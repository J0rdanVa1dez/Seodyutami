#include <iostream>
#include "imageFusion.h"
#include "changeViewPoint.h"

using namespace std;

int main()
{
	Fusion fusion;
	CVP cvp;
	IplImage* disparity = cvLoadImage("image/test_disparity.jpg");
	IplImage* rightImage = cvLoadImage("image/test_R.jpg");
	IplImage* leftImage = cvLoadImage("image/test_L.jpg");
	IplImage* convertImage = NULL;
	IplImage* multiFocusImage=NULL;

	//cvp class --> ���� ���� �ذ�
	cvp.setimg(disparity, leftImage, rightImage);	//Image ����(���и�Ƽ, ����, ������)
	cvp.runcvt(&convertImage);						//�������� �ذ��Ͽ� dst�̹����� ����

	//fusion class --> Multi Focus Image Fusion
	fusion.setimg(rightImage, convertImage);		//Image ����(������ �ٸ� ������ ���� �ΰ��� �̹���)
	fusion.sml(&multiFocusImage);					//Multi Focus Image Fusion�� ������ �����  dst�̹����� ����

	cvShowImage("MultiFocusImage", multiFocusImage);
	cvShowImage("convertImage", convertImage);
	cvShowImage("disparity", disparity);
	cvShowImage("leftImage", leftImage);
	cvShowImage("rightImage", rightImage);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&disparity);
	cvReleaseImage(&rightImage);
	cvReleaseImage(&leftImage);
	cvReleaseImage(&convertImage);
	cvReleaseImage(&multiFocusImage);


	return 0;
}