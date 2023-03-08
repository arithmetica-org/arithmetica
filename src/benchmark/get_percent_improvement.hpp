#pragma once

#include <algorithm>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

static void
replace_all (std::string &str, const std::string &from, const std::string &to)
{
  if (from.empty ())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find (from, start_pos)) != std::string::npos)
    {
      str.replace (start_pos, from.length (), to);
      start_pos += to.length ();
    }
}

static inline size_t
curl_get_response (char *buffer, size_t itemsize, size_t nitems,
                   void *ignorethis)
{
  size_t bytes = itemsize * nitems;
  return bytes;
}

static size_t
curl_write_data (char *ptr, size_t size, size_t nmemb, void *inputstream)
{
  std::ostringstream *stream = (std::ostringstream *)inputstream;
  size_t count = size * nmemb;
  stream->write (ptr, count);
  return count;
}

static std::vector<std::pair<std::string, double> >
get_uid_details (std::string uid, std::vector<nlohmann::json> json_objects)
{
  std::vector<std::pair<std::string, double> > uid_details;
  for (auto &json_object : json_objects)
    {
      if (json_object["identifier"] != uid)
        {
          continue;
        }

      for (auto &[name, hertz] : json_object["benchmarks"].items ())
        {
          std::string function_name = name;
          double runtime_hertz = hertz;
          uid_details.push_back (
              std::make_pair (function_name, runtime_hertz));
        }
    }
  return uid_details;
}

// Return a vector of percentage improvements / regressions, positive values
// are improvements, negative values are regressions.
std::vector<std::pair<std::string, double> >
get_percent_improvement (std::string uid_1, std::string uid_2,
                         std::string upload_server)
{
  CURL *curl = curl_easy_init ();
  std::ostringstream stream;

  std::string url = "https://docs.google.com/forms/d/e/" + upload_server
                    + "/viewanalytics";

  curl_easy_setopt (curl, CURLOPT_URL, url.c_str ());
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, curl_write_data);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, &stream);
  curl_easy_perform (curl);
  curl_easy_cleanup (curl);

  std::string respose_contents = stream.str ();

  // Each json object starts with <{\"identifier\"> and ends with <}}>, where
  // <> represent quotes.
  std::vector<std::string> json_objects_str;
  std::string::size_type start = respose_contents.find ("{\\\"identifier");
  while (start != std::string::npos)
    {
      std::string::size_type end = respose_contents.find ("}}", start);
      if (end != std::string::npos)
        {
          json_objects_str.push_back (
              respose_contents.substr (start, end - start + 2));
          start = respose_contents.find ("{\\\"identifier", end);
        }
      else
        {
          start = end;
        }
    }

  for (auto &json_object : json_objects_str)
    {
      replace_all (json_object, "\\n", "");
      replace_all (json_object, "\\", "");
    }

  // Parse the json objects.
  std::vector<nlohmann::json> json_objects;
  for (auto &json_object_str : json_objects_str)
    {
      json_objects.push_back (nlohmann::json::parse (json_object_str));
    }

  // Get the details of the two uids.
  std::vector<std::pair<std::string, double> > uid_1_details
      = get_uid_details (uid_1, json_objects);
  std::vector<std::pair<std::string, double> > uid_2_details
      = get_uid_details (uid_2, json_objects);

  if (uid_1_details.empty () || uid_2_details.empty ())
    {
      return { { "Previous commit not found on the specified upload server.",
                 0 } };
    }

  // Calculate the percentage improvement / regression. Each element in the
  // vector is the number of runs per second (Hz).
  std::vector<std::pair<std::string, double> > percent_improvements;
  for (auto &uid_1_detail : uid_1_details)
    {
      for (auto &uid_2_detail : uid_2_details)
        {
          if (uid_1_detail.first == uid_2_detail.first)
            {
              double percent_improvement
                  = (uid_1_detail.second - uid_2_detail.second)
                    / uid_1_detail.second;
              percent_improvements.push_back (
                  std::make_pair (uid_1_detail.first, percent_improvement));
            }
        }
    }

  return percent_improvements;
}