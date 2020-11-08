#include <gtest/gtest.h>

#include "../../detector/include/FaceDetectorDLL.h"


static const FaceDetectorDLL detector("detector_lib");

static int FoundFacesCount(const std::string& image_path) noexcept {
	return (int) detector.CallDetectFaces(cv::imread(image_path), image_path).size();
}


TEST(DetectorLibTest, FacesCountImage1) {
	EXPECT_EQ(FoundFacesCount("./TestDirectory/test.jpg"), 0);
}

TEST(DetectorLibTest, FacesCountImage2) {
	EXPECT_EQ(FoundFacesCount("./TestDirectory/f1/1.jpg"), 6);
}

TEST(DetectorLibTest, FacesCountImage3) {
	EXPECT_EQ(FoundFacesCount("./TestDirectory/f1/3.jpg"), 28);
}

TEST(DetectorLibTest, FacesCountImage4) {
	EXPECT_EQ(FoundFacesCount("./TestDirectory/f1/f11/2.jpg"), 2);
}

TEST(DetectorLibTest, FacesCountImage5) {
	EXPECT_EQ(FoundFacesCount("./TestDirectory/f2/4.webp"), 4);
}

TEST(DetectorLibTest, FacesCountImage6) {
	EXPECT_EQ(FoundFacesCount("./TestDirectory/f2/5.jpg"), 2);
}