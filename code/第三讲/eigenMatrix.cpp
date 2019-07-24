#include<iostream>
#include<ctime>

using namespace std;

#include<Eigen/Core>

#include<Eigen/Dense>

#define MATRIX_SIZE 50

int main(int argc, char const *argv[])
{
	Eigen::Matrix<float,2,3> matrix_23;
	Eigen::Vector3d v_3d; //实际上就是Eigen::Matrix<double,3,1>

	Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero(); //3x3矩阵初始化为0

	Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_dynamic;//动态大小的矩阵

	Eigen::MatrixXd matrix_x; //动态大小矩阵的简单表示形式

	matrix_23 << 1,2,3,4,5,6;

	cout<<matrix_23<<endl;

	//循环访问矩阵中的元素
	cout<<"------------------------\n";
	cout<<"循环访问矩阵中的元素"<<endl;
	for(int i=0;i<2;i++){
		for(int j =0;j<3;j++){
			cout<<matrix_23(i,j)<<endl;
		}
	}
	cout<<"------------------------\n";

	v_3d<<3,2,1;


	//矩阵和向量相乘,实际上是矩阵和矩阵相乘, 所以在计算中要进行转换

	// 以下是一个错误的示例,编译报错
	//Eigen::Matrix<double,2,1> result_wrong_type = matrix_23 * v_3d;

	// 正确的示例
	Eigen::Matrix<double,2,1> result = matrix_23.cast<double>() * v_3d;
	cout<<"matrix_23.cast<double>() * v_3d\n";
	cout<<result<<endl;
	cout<<"------------------------\n";
	// 需要注意的是矩阵的维度也不能搞错

	matrix_33 = Eigen::Matrix3d::Random();
	cout<<"原矩阵\n";
	cout<<matrix_33<<endl;
	cout<<"转置\n";
	cout<<matrix_33.transpose()<<endl;
	cout<<"个元素和\n";
	cout<<matrix_33.sum()<<endl;
	cout<<"矩阵的迹\n";
	cout<<matrix_33.trace()<<endl;
	cout<<"数乘\n";
	cout<<matrix_33*10<<endl;
	cout<<"逆\n";
	cout<<matrix_33.inverse()<<endl;
	cout<<"行列式\n";
	cout<<matrix_33.determinant()<<endl;
	cout<<"------------------------\n";

	cout<<"特征值"<<endl;
	// 使用实对称矩阵保证对角化成功
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
	cout<<"Eigen values\n"<<eigen_solver.eigenvalues()<<endl;
	cout<<"Eigen vectors\n"<<eigen_solver.eigenvectors()<<endl;

	//解方程
	//求解方程 matrix_NN * x = v_Nd
	//直接求逆是最简单的,但是直接求逆运算量大

	Eigen::Matrix<double,MATRIX_SIZE,MATRIX_SIZE> matrix_NN;
	matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE);

	Eigen::Matrix<double,MATRIX_SIZE,1> v_Nd;
	v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE,1);

	//计时器
	clock_t time_stt = clock();

	//直接求逆
	Eigen::Matrix<double,MATRIX_SIZE,1> x = matrix_NN.inverse()*v_Nd;
	cout<<"time use in normal inverse is:"<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;

	// 通常用矩阵分解来求, 例如QR分解,速度会更快
	time_stt = clock();
	x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
	cout<<"time use in Qr composition is : "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC<<"ms"<<endl;
	return 0;
}

//编译
// g++ eigenMatrix.cpp -o eigenMtrixTest.exe -I /usr/include/eigen3