#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include <opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#pragma comment(lib,"opencv_world490d.lib")
#else
#pragma comment(lib,"opencv_world490.lib")
#endif

int main() {

    Mat img1 = imread("C:/Users/choij/Desktop/L3.jpg"); // 왼쪽 이미지
    Mat img2 = imread("C:/Users/choij/Desktop/R3.jpg"); // 오른쪽 이미지

    if (img1.empty() || img2.empty()) {
        cout << "이미지를 불러오지 못했습니다." << endl;
        return -1;
    }

    
    Ptr<ORB> orb = ORB::create();
    vector<KeyPoint> Featurepoint1, Featurepoint2;
    Mat descriptors1, descriptors2;

    orb->detectAndCompute(img1, Mat(), Featurepoint1, descriptors1);
    orb->detectAndCompute(img2, Mat(), Featurepoint2, descriptors2);

    BFMatcher matcher(NORM_HAMMING, true);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    
    
    sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
        return a.distance < b.distance;
        });

    auto numGoodMatches = matches.size() * 0.2; // 상위 20%
    vector<DMatch> goodMatch(matches.begin(), matches.begin() + numGoodMatches);


    Mat good_matches;
    drawMatches(img1, Featurepoint1, img2, Featurepoint2, goodMatch, good_matches);
    

    vector<Point2f> leftPoint, rightPoint;
    for (size_t i = 0;i <goodMatch.size(); i++) {
        leftPoint.push_back(Featurepoint1[goodMatch[i].queryIdx].pt);
        rightPoint.push_back(Featurepoint2[goodMatch[i].trainIdx].pt);
    }

    Mat Homography_ransac = findHomography(rightPoint, leftPoint, RANSAC);
    Mat Homography_leastsquares = findHomography(rightPoint, leftPoint, 0);


    Mat result_ransac, result_leastsquares;
    Size result_size(img1.cols * 2, img1.rows);

    warpPerspective(img2, result_ransac, Homography_ransac, result_size);
    Mat ROI_ransac(result_ransac, Rect(0, 0, img1.cols, img1.rows));
    img1.copyTo(ROI_ransac);

    warpPerspective(img2, result_leastsquares, Homography_leastsquares, result_size);
    Mat ROI_leastsquares(result_leastsquares, Rect(0, 0, img1.cols, img1.rows));
    img1.copyTo(ROI_leastsquares);

    imshow("Good Matches", good_matches);
    waitKey(0);
    
    imshow("Stitched Image (RANSAC)", result_ransac);
   

    imshow("Stitched Image (Least Squares)", result_leastsquares);
    waitKey(0);

    return 0;
}
