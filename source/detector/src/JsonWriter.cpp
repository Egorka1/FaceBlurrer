#include "JsonWriter.h"


JsonWriter::JsonWriter(const std::string& dir_path) noexcept : m_sSaveDir(dir_path) {}

JsonWriter::~JsonWriter() {
	m_nRoot.add_child("Images", m_nImages);
	boost::property_tree::write_json(m_sSaveDir.c_str(), m_nRoot);
}

void JsonWriter::AddImageResults(const std::string& input_path, const std::string& output_path, const std::vector<cv::Rect>& faces) noexcept {
	boost::property_tree::ptree image_node;

	image_node.put("Image path", input_path);
	image_node.put("Output path", output_path);
	image_node.put("Faces count", faces.size());

	boost::property_tree::ptree faces_node;
	for (const cv::Rect& face : faces) {
		boost::property_tree::ptree face_node;

		boost::property_tree::ptree x_node, y_node, w_node, h_node;
		x_node.put("x", face.x);
		y_node.put("y", face.y);
		w_node.put("w", face.width);
		h_node.put("h", face.height);

		face_node.add_child("", x_node);
		face_node.add_child("", y_node);
		face_node.add_child("", w_node);
		face_node.add_child("", h_node);

		faces_node.add_child("", face_node);
	}
	image_node.add_child("Faces coordinates", faces_node);

	m_nImages.add_child("", image_node);
}