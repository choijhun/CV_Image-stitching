# Image-stitching
Feature matching , Homography를 이용한 두 이미지를 합성한다.
# ORB feature detection
- 각 이미지에서 feature point 와 Descriptor 추출
- feature point로는 회전이나 크기 변화에도 대응할 수 있는 점들을 사용
# Feature Matching
- Hamming distance를 이용하여 feature point간 유사도 비교
- matching 결과를 distance 기준으로 sort 후에 상위 20%의 keypoint 만 사용
- 상위의 kp만 사용하여 homography의 안정성을 높힘.
# Homography
- 두 이미지에서 대응되는 kp들을 이용하여 한 이미지의 좌표를 다른 이미지의 좌표계로 변환하는 perspective transform 행렬 새성
- 오른쪽 이미지를 시점을 왼쪽 이미지의 시점에 맞춤
# Least Square vs RANSAC
- Least square는 모든 matching point를 사용하여 homography가 안정적이지 않을 수 있음
- RANSAC은 일관된 matching point들만 사용하여 homography가 안정적

# Left image, Right image
<img width="248" height="331" alt="L3" src="https://github.com/user-attachments/assets/61fba665-e98b-49e2-9a81-30ad54711ffd" />
<img width="248" height="331" alt="R3" src="https://github.com/user-attachments/assets/a8d42832-0a5b-4991-ae98-64d153503d39" />

# feature points
<img width="447" height="331" alt="good_matches" src="https://github.com/user-attachments/assets/1693f52c-e886-4663-b3e4-a3888ec4e866" />

# result
<img width="447" height="331" alt="result_ransac" src="https://github.com/user-attachments/assets/21f2753d-b8bb-46ad-8ab8-144b843760aa" />
