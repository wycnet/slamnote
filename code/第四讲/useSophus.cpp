#include<iostream>
#include<cmath>

using namespace std;

#include<Eigen/Core>
#include<Eigen/Geometry>
#include"Sophus/sophus/so3.h"
#include"Sophus/sophus/se3.h"



int main(int argc, char const *argv[])
{
	Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2,Eigen::Vector3d(0,0,1)).toRotationMatrix();
	cout<<"沿着Z轴旋转90度\n"<<R<<endl;
	
	//SO(3)可以直接从旋转向量构造
	Sophus::SO3 SO3_R(R);
	//从旋转向量构造
	Sophus::SO3 SO3_v(0,0,M_PI/2);

	//构建四元数
	Sophus::Quaterniond q(R);
	Sophus::SO3 SO3_q(q);

	cout<<"SO(3) from matrix:"<<SO3_R<<endl;
	cout<<"SO(3) from vector:"<<SO3_v<<endl;
	cout<<"SO(3) from quaternion:"<<SO3_q<<endl;

	//使用对数映射获取它的李代数
	

	return 0;
}


// g++ ./Sophus/sophus/s[oe]3.cpp useSophus.cpp -o useSophus.exe   -I /usr/include/eigen3 