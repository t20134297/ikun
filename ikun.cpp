#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat add_cxk(Mat source, Mat cxk) //这个函数的功能是将宇宙无敌kunkun加入到原图片的右下角
{
  int row, col;
  row = cxk.rows;   //获得宇宙无敌Kunkun原始图片的高度
  col = cxk.cols;   //获得宇宙无敌Kunkun原始图片的宽度

  int times, new_row, new_col;
  times = 3;  //将宇宙无敌kunkun的图片缩小为原来的三倍
  new_row = row / times;  //宇宙无敌kunkun缩小后的图片的高度
  new_col = col / times;   //宇宙无敌kunkun缩小后的图片的宽度

  int row_start, col_start;
  row_start = row - new_row - 2;
  col_start = col - new_col - 2;  //设置kunkun图片在合成图片中的左上角的坐标

  for(int i = 0; i < new_row; i = i + 1)
  {
    for(int j = 0; j < new_col; j = j + 1)
    {
      source.at<Vec3b>(i + row_start, j + col_start)[0] = cxk.at<Vec3b>(i * times, j * times)[0];
      source.at<Vec3b>(i + row_start, j + col_start)[1] = cxk.at<Vec3b>(i * times, j * times)[1];
      source.at<Vec3b>(i + row_start, j + col_start)[2] = cxk.at<Vec3b>(i * times, j * times)[2];
    }
  }                              //将待融合的图片的右下角使用kunkun的图片来填充
  return source;   //这就是在左下角加入了Kunkun帅照的合成图片
}

int main()
{
  VideoCapture cxk_video("cxk.mp4"); //读取kunkun的视频
  VideoCapture cry_video("cry.mp4");  //读取众明星哭泣的视频
  int counts_kk = cxk_video.get(CV_CAP_PROP_FRAME_COUNT); //获得读取的kunkun视频中一共有多少帧图片
  int fps = cxk_video.get(CV_CAP_PROP_FPS);  //获得kunkun视频的帧率
  int frame_width = cry_video.get(CV_CAP_PROP_FRAME_WIDTH); //获得众明星视频每一帧图像的宽度
  int frame_height = cry_video.get(CV_CAP_PROP_FRAME_HEIGHT);//获得众明星视频每一帧图像的高度

  Mat kk, cry, add;

  // cxk_video >> kk;
  // cry_video >> cry;
  // add = add_cxk(cry,kk);
  // imwrite("ikun.jpg",add); // 生成一张kunkun和明星迷妹迷弟的合照

  string name = "ikun.mpeg"; //合成视频的名字必须是这个令人疯狂的名字
  VideoWriter video = VideoWriter(name,CV_FOURCC('M','P','E','G'),fps,Size(frame_width,frame_height),1); //设置合成后的视频的格式
  while(counts_kk > 2)   //控制循环的次数，Kunkun视频中的所有帧数都用完了，也就结束了
  {
    cxk_video >> kk;   //读取kunkun视频中的一帧图像
    cry_video >> cry;
    add = add_cxk(cry,kk); //将两张图片加入到神奇的函数中
    --counts_kk;
    video.write(add);  //将合成后的图片加入到新生成的视频中
  }
  return 1;
}
