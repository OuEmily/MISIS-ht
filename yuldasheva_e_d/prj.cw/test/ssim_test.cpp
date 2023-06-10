
#include <ssim/ssim.hpp>

int main(int argc, char** argv) {
    
    cv::CommandLineParser parser(argc, argv, "{image1 im1| |The first image}{image2 im2| |The second image}{heatmap| |Save heatmap}");
   // parser.addArgument("{image2| |The second image}");

    std::string image1Path = parser.get<std::string>("image1");
    std::string image2Path = parser.get<std::string>("image2");
    //std::string HeatMapPath = parser.get<std::string>("heatmap");
    
    if (image1Path.empty() || image2Path.empty()) {
        std::cerr << "Cannot open or read the images!" << std::endl;
        return -1;
    }
    SSIM test;
    test.im1_ = cv::imread(image1Path);
    test.im2_ = cv::imread(image2Path);

    if (test.im1_.empty() || test.im2_.empty()) {
        std::cerr << "Error reading images!" << std::endl;
        return -1;
    }
    //cv::cvtColor(image1, image1, cv::COLOR_BGR2GRAY);
    //cv::cvtColor(image2, image2, cv::COLOR_BGR2GRAY);
    //cv::resize(image1, image1, image2.size());

    
    
    std::pair<cv::Scalar, cv::Mat> ssim =  test.Ssim();
    std::cout << "SSIM: " << ssim.first.val[0] << std::endl;

    cv::Mat heatmap = test.HeatMap();
    //cv::imshow("SSIM Map", heatmap);

    if (parser.has("heatmap")) {
        std::string HeatMapPath = parser.get<std::string>("heatmap");
        cv::imwrite(HeatMapPath, heatmap);
    }
    
    
    cv::waitKey(0);
    return 0;


}
