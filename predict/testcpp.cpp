#define	USE_OPENCV	1
#include <caffe/caffe.hpp>

#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif  // USE_OPENCV
#include <string>
#include <vector>
#include"directory.h"

using namespace caffe;
using namespace std;

//人脸裁剪,输入为人脸框+图片
cv::Mat Cropimage(cv::Mat img, int x1 = 478, int x2 = 1126, int y1 = 1057, int y2 = 1705)
{

	float scale = 0.4f;
	int w = x2 - x1;
	int h = y2 - y1;


	int miny = max(0, int(y1 - scale*h));
	int minx = max(0, int(x1 - scale*w));
	int maxy = min(img.rows, int(y1 + (1 + scale)*h));
	int maxx = min(img.cols, int(x1 + (1 + scale)*w));
	cv::Mat roi = img(cv::Rect(minx, miny, maxx - minx, maxy - miny));

	int maxlenght = max(roi.rows, roi.cols);
	cv::Mat img0 = cv::Mat::zeros(maxlenght, maxlenght, CV_8UC3);


	int newx1 = maxlenght*.5 - roi.cols * .5;
	int newy1 = maxlenght*.5 - roi.rows * .5;
	int neww = (maxlenght*.5 + roi.cols * .5) - newx1;
	int newh = (maxlenght*.5 + roi.rows * .5) - newy1;
	cv::Rect temp(newx1, newy1, neww, newh);
	roi.copyTo(img0(temp));

	return roi;

}
int race_predict(const boost::shared_ptr< Net<float> > &net,cv::Mat img, int x1, int x2, int y1, int y2)
{
    //随机标签
  vector<int> labelVector;
  labelVector.push_back(0);
  
//第二步:图片数据预处理
  cv::Mat image;
 // cv::Mat Cropimage(cv::Mat img, int x1 = 478, int x2 = 1126, int y1 = 1057, int y2 = 1705)
  cv::Size size(256,256);
  cv::resize(img,image,size);//缩放到指定大小

  //输入图片
  vector<cv::Mat> imageVector;
  imageVector.push_back(image);




  // 载入图片数据到caffe中
  float loss = 0.0;
  shared_ptr<MemoryDataLayer<float> > memory_data_layer;
  memory_data_layer = boost::static_pointer_cast<MemoryDataLayer<float> >(net->layer_by_name("data"));
  memory_data_layer->AddMatVector(imageVector,labelVector);

  //神经网络前向计算
  vector<Blob<float>*> results = net->ForwardPrefilled(&loss);

   // 获取结果
  const float* argmaxs = results[1]->cpu_data();
  float max = 0;
  float max_i = 0;
  for (int i = 0; i < 4; ++i) {
    float value = results[0]->cpu_data()[i];
    std::cout <<value << std::endl;
    if (max < value){
      max = value;
      max_i = i;
    }
  }
  return max_i;
}
boost::shared_ptr< Net<float> > race_init(string proto="model/gender_train_val.prototxt",string model="model/caffenet_train_iter_v3.caffemodel")
{
  //第一步.加载模型
  // 设置计算只采用CPU
  Caffe::set_mode(Caffe::CPU);
  //加载网络模型
  boost::shared_ptr< Net<float> > net(new caffe::Net<float>(proto,caffe::TEST));
  //加载均值文件
  net->CopyTrainedLayersFrom(model);
  
  return net;
}
int main(int argc, char** argv)
{

  vector<string>labels;
  labels.push_back("black");
  labels.push_back("brown");
  labels.push_back("white");
  labels.push_back("yellow");
  boost::shared_ptr< Net<float> > net=race_init();

  
  
   cv::Mat image= cv::imread("image/12.jpg");
   int maxi=race_predict(net,image,1,1,1,1);
   
  
   //显示结果
  cv::imshow(labels[maxi],image);
  cv::moveWindow(labels[maxi], 100, 100);
  cv::waitKey(0);
  
  
  
  
  



  return 0;
}

