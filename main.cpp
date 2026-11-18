#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>

int main() {
    cv::VideoCapture cam(0);
    if (!cam.isOpened()) {
        std::cerr << "Ошибка: не удалось открыть веб-камеру!" << std::endl;
        return -1;
    }

    std::string dirName = "/home/vladimir/Study/OpenCV/College_code/KT4";
    std::filesystem::create_directory(dirName);

    std::cout << "Камера готова.\n"
              << "Нажмите 'r' или 'к' для записи кадров в папку.\n"
              << "Нажмите 'ESC' для выхода." << std::endl;

    cv::Mat frame;
    bool isRecording = false;
    int frameCount = 0;

    while (true) {
        cam >> frame;
        if (frame.empty()) break;

        if (isRecording) {
            std::ostringstream ss;
            ss << dirName << "/frame_" << std::setw(4) << std::setfill('0') << frameCount++ << ".jpg";
            cv::imwrite(ss.str(), frame);

            cv::putText(frame, "REC", cv::Point(30, 50),
                        cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Frame Recorder", frame);

        int key = cv::waitKey(30);
        if (key == 27) {
            break;
        } else if (key == 'r' || key == 'R' || key == 'к' || key == 'К') {
            isRecording = !isRecording;
            std::cout << "Запись кадров: " << (isRecording ? "ВКЛ" : "ВЫКЛ") << std::endl;
        }
    }

    cv::destroyAllWindows();
    return 0;
}