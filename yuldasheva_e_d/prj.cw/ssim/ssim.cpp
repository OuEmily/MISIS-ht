
#include <ssim/ssim.hpp>

/**
 * @brief 
 * 
 * Функция высчитывает индекс SSIM на основе двух изображений, предварительно обрабатывая их для более удобной работы и точных подсчетов
 * 
 * @param im1 
 * @param im2 
 * @return std::pair<cv::Scalar, cv::Mat> 
 */

std::pair<cv::Scalar, cv::Mat> SSIM::Ssim() {
    
     cv::Mat im1, im2;
    im1_.copyTo(im1);
    im2_.copyTo(im2);
     


    //cv::cvtColor(im1, im1, cv::COLOR_BGR2GRAY);
    //cv::cvtColor(im2, im2, cv::COLOR_BGR2GRAY);

    cv::resize(im1, im1, im2.size());

    
    /**
     * @brief переменные в которые запишутся значения динамического диапазона
     * 
     */
    double min_val_1, max_val_1, min_val_2, max_val_2, L_1, L_2; 

    cv::minMaxLoc(im1, &min_val_1, &max_val_1);
    L_1 = max_val_1 - min_val_1;
    //std::cout << L_1 << std::endl;

    cv::minMaxLoc(im2, &min_val_2, &max_val_2);
    L_2 = max_val_2 - min_val_2;
    //std::cout << L_2 << std::endl;

    double K1 = 0.01 , K2 = 0.03, C1 = 0, C2 = 0, C3 = 0;
    //вычисляем С1, C2
    C1 = pow(K1 * L_1, 2);
    C2 = pow(K2 * L_2, 2);
    
    //std::cout << C1 << std::endl;
    //std::cout << C2 << std::endl;
    /**
     * @brief  конвертируем матрицу изображения во float для болле точных вычислений
     * 
     */
    cv::Mat im1_f, im2_f;
    im1.convertTo(im1_f, CV_32F);
    im2.convertTo(im2_f, CV_32F);

    /**
     * @brief  возводим матрицы в квадрат для вычисления сигмы
     * 
     */
    cv::Mat im1_2 = im1.mul(im1); //im1^2
    cv::Mat im2_2 = im2.mul(im2); // im2^2
    cv::Mat im12 = im1.mul(im2); //im1*im2

    /**
     * @brief создаем окно-блок пикселей для которого будем вычислять индекс ssim
     * 
     */
    int windowSize = 11;
    cv::Mat window(windowSize, windowSize, CV_32F);

    /**
     * @brief  вычисляем среднее знаечение по окну
     * 
     */
    cv::Mat mu1, mu2, mu12;
    //cv::boxFilter(im1, mu1, CV_32F, cv::Size(windowSize, windowSize)); // среднеее по x
    //cv::boxFilter(im2, mu2, CV_32F, cv::Size(windowSize, windowSize)); // среднее по у
    cv::GaussianBlur(im1, mu1, cv::Size(windowSize, windowSize), 1.5, 1.5, cv::BORDER_WRAP);
    cv::GaussianBlur(im2, mu2, cv::Size(windowSize, windowSize), 1.5, 1.5, cv::BORDER_WRAP);

    /**
     * @brief вычисляем необходимые значение мю для конечной формулы
     * 
     */
    cv::Mat mu1_2 = mu1.mul(mu1); // mu1^2
    cv::Mat mu2_2 = mu2.mul(mu2); // mu2^2
    cv::Mat mu1_mu2 = mu1.mul(mu2); // mu1*mu2

    /**
     * @brief вычисляем среднеквадратическое по окну
     * 
     */
    cv::Mat sigma1_2, sigma2_2, sigma12;
    cv::GaussianBlur(im1_2, sigma1_2, cv::Size(windowSize, windowSize), 1.5, 1.5, cv::BORDER_WRAP);
    cv::GaussianBlur(im2_2, sigma2_2, cv::Size(windowSize, windowSize), 1.5, 1.5, cv::BORDER_WRAP);
    cv::GaussianBlur(im12, sigma12, cv::Size(windowSize, windowSize), 1.5, 1.5, cv::BORDER_WRAP);
   

    /**
     * @brief вычисляем среднеквадратическое отклонение
     * 
     */
    sigma1_2 -= mu1_2;// sigma1^2
    sigma2_2 -= mu2_2;// sigma2^2
    sigma12 -= mu1_mu2;// sigma1*sigma2

    /**
     * @brief вычисляем ssim в виде матрицы для всего изображения (по каждому блоку пикселей)
     * 
     */
    cv::Mat ssim_i;
    cv::Mat num = (2 * mu1_mu2 + C1).mul(2 * sigma12 + C2);
    cv::Mat denum = (mu1_2 + mu2_2 + C1).mul(sigma1_2 + sigma2_2 + sigma12);
    cv::divide(num, denum, ssim_i);

    /**
     * @brief находим среднее значение по матрице ssim по блокам6 чтобы вычислить среднее значение по всему изображению
     * 
     */
    cv::Scalar ssim = mean( ssim_i )[0];
    /**
     * @brief возвращаем кортеж, состоящий из среднего знаечения матрицы по окну(матрица 2*2 тк изображение одноканальное то, все элементы кроме 1,1 равны 0)
     *  и матрицу индексов для каждого блока пикселей
     * 
     * @return return 
     */
    return std::make_pair(ssim, ssim_i);

}

/**
 * @brief 
 * 
 * Функция создает тепловую карту на основе матрицы индексов SSIM, высчитанных для каждого блока пикселей 8*8
 * 
 * @param im1_ 
 * @param im2_ 
 * @return cv::Mat 
 */
 cv::Mat SSIM::HeatMap() {
    cv::Mat im1, im2;
    im1_.copyTo(im1);
    im2_.copyTo(im2);
    /**
     * @brief фиксируем значения, возвращаемые методом Ssim в переменную
     * 
     */
    std::pair<cv::Scalar, cv::Mat> ssim =  SSIM::Ssim(); 
    double min_val, max_val;
    cv::Mat ssim_map_visual;
    /**
     * @brief нормалицуем матрицу для создания тепловой карты
     * 
     */
    cv::normalize(ssim.second, ssim_map_visual, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::Mat heatmap;
    /**
     * @brief Сщздаем тепловую карту
     * 
     */
    cv::applyColorMap(ssim_map_visual, heatmap, cv::COLORMAP_JET);
    //cv::namedWindow("SSIM Map", cv::WINDOW_NORMAL);
    //cv::imshow("SSIM Map", heatmap);
    return heatmap;
}
