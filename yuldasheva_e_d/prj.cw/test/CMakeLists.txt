add_executable(ssim_test "ssim_test.cpp")
target_link_libraries( ssim_test ssim ${OpenCV_LIBS})
install(TARGETS ssim_test DESTINATION bin)