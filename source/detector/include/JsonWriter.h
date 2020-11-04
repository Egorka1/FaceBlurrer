#pragma once

#include <opencv2/opencv.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


class JsonWriter {
public:
	JsonWriter(const std::string&) noexcept;
	~JsonWriter();

	void AddImageResults(const std::string&, const std::string&, const std::vector<cv::Rect>&) noexcept;

private:
	boost::property_tree::ptree m_nRoot;
	boost::property_tree::ptree m_nImages;

	std::string m_sSaveDir;
};