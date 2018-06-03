#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
	cv::CascadeClassifier face_cascade;

	if (!face_cascade.load("cascade.xml")) {
		std::cout << "Failed to load file" << std::endl;
		return -1;
	}

	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		std::cout << "exit" << std::endl;
		return -1;
	}

	long count = 0;

	while (true)
	{
		std::vector<cv::Rect> faces;
		cv::Mat frame;
		cv::Mat cropImg;

		cap >> frame;

		count++;

		if (!frame.empty()) {
			face_cascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200));

			std::cout << faces.size() << " faces detected" << std::endl;
			std::string frameset = std::to_string(count);
			std::string faceset = std::to_string(faces.size());

			int width = 0, height = 0;
			// region of interest
			cv::Rect roi;

			for (int i = 0; i < faces.size(); ++i)
			{
				cv::Rect& face = faces[i];

				cv::rectangle(frame, cv::Point(face.x, face.y), cv::Point(face.x + face.width, face.y + face.height), cv::Scalar(255, 0, 255), 1, 8, 0);

				std::cout << face.width << "x" << face.height << std::endl;
				width = face.width;
				height = face.height;

				roi = face;

				cropImg = frame(face);
				//cv::imshow("ROI", cropImg);
				//cv::waitKey(5);
			}

			std::string wi = std::to_string(width);
			std::string he = std::to_string(height);

			cv::putText(frame, "Frames: " + frameset, cv::Point(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 255, 0), 1, CV_AA);
			cv::putText(frame, "Faces Detected: " + faceset, cv::Point(30, 60), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 255, 0), 1, CV_AA);
			cv::putText(frame, "Resolution " + wi + " x " + he, cv::Point(30, 90), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 255, 0), 1, CV_AA);


			cv::imshow("Face", frame);
		}
		if (cv::waitKey(30) >= 0) break;
	}

	return 0;
}
