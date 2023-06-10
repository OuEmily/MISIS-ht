#pragma once

#ifndef SSIMHPP
#define SSIMHPP

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


class SSIM{
    public:
        SSIM() = default;
        SSIM(const SSIM& rhs) = default;
        SSIM& operator=(const SSIM& rhs) = default;
        SSIM& operator=(const cv::Mat& rhs);
        ~SSIM() = default;
        SSIM(SSIM&& other) noexcept = default;
        SSIM& operator=(SSIM&& other) = default;
        /**
         * @brief 
         * 
         * Функция высчитывает индекс SSIM в виде матрицы для каждого блока пикселей и среднее значение индекса для всего изображения. Вычисления делаются на основе двух изображений, предварительно обрабатанных для более удобной работы и точных подсчетов.
         * 
         * @param im1_ первое сравниваемое изображение
         * @param im2_ второе сравниваемое изображение
         * @return std::pair<cv::Scalar, cv::Mat> 
         */
        std::pair<cv::Scalar, cv::Mat> Ssim();

        /**
         * @brief 
         * 
         * Функция создает тепловую карту на основе матрицы индексов SSIM, высчитанных для каждого блока пикселей 8*8
         * 
         * @param im1_ первое сравниваемое изображение
         * @param im2_ второе сравниваемое изображение
         * @return cv::Mat 
         */
        cv::Mat HeatMap();
        /**
         * @brief первое сравниваемое изображение
         * 
         */
        cv::Mat im1_; 
        /**
         * @brief второе сравниваемое изображение
         * 
         */
        cv::Mat im2_;

};
#endif
