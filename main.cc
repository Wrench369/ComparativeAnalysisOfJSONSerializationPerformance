#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "ScoperTimer.hh"
#include "nlohmann/json.hpp"
#include "yyjson.h"

using json = nlohmann::json;

std::string serializeDataByYYJson(
    const std::vector<std::unordered_map<std::string, std::string>>
        &dataVector) {
  yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
  yyjson_mut_val *root = yyjson_mut_obj(doc);
  yyjson_mut_doc_set_root(doc, root);

  yyjson_mut_val *json_arr = yyjson_mut_arr(doc);

  // 遍历vector中的每个unordered_map
  for (const auto &dataMap : dataVector) {
    // 为每个unordered_map创建一个JSON对象，并添加到数组中
    yyjson_mut_val *map_val = yyjson_mut_obj(doc);

    // 遍历unordered_map中的每个键值对
    for (const auto &pair : dataMap) {
      // 创建键和值的JSON字符串，并添加到对象中
      yyjson_mut_obj_add_str(doc, map_val, pair.first.c_str(),
                             pair.second.c_str());
    }
    yyjson_mut_arr_append(json_arr, (yyjson_mut_val *)map_val);
  }

  yyjson_mut_doc_set_root(doc, (yyjson_mut_val *)json_arr);

  // 序列化JSON文档到字符串
  char *json_str = yyjson_mut_write(doc, 0, NULL);

  // 将序列化后的JSON字符串复制到std::string
  std::string jsonStr(json_str);

  // 清理资源
  free(json_str);
  yyjson_mut_doc_free(doc);

  return jsonStr;
}

std::string serializeDataByNlohmann(
    const std::vector<std::unordered_map<std::string, std::string>>
        &dataVector) {
  json jsonData = json::array();

  for (const auto &innerMap : dataVector) {
    json jsonObj = json::object();
    for (const auto &pair : innerMap) {
      jsonObj[pair.first] = pair.second;
    }
    jsonData.push_back(jsonObj);
  }

  return jsonData.dump();
}

int main(int argc, char **argv) {
  // 创建一个包含unordered_map<string, string>元素的大vector
  std::vector<std::unordered_map<std::string, std::string>> dataVector;

  // 添加一些数据到vector中
  for (int i = 0; i < 10000; ++i) {
    std::unordered_map<std::string, std::string> dataMap;
    dataMap["key1"] = "value1";
    dataMap["key2"] = "value2";
    dataVector.push_back(dataMap);
  }

  Timer timer1;
  // 序列化dataVector中的数据为JSON格式
  std::string json_str1 = serializeDataByYYJson(dataVector);

  double elapsed_time1 = timer1.Elapsed();
  std::cout << "Elapsed time: " << elapsed_time1 << "seconds" << std::endl;

  Timer timer2;
  std::string json_str2 = serializeDataByNlohmann(dataVector);

  double elapsed_time2 = timer2.Elapsed();
  std::cout << "Elapsed time: " << elapsed_time2 << "seconds" << std::endl;

  // std::cout << "Serialized JSON: " << json_str2 << std::endl;
  // 释放内存

  return 0;
}