#include<ostream>
#include<opencv2/core/core.hpp>
#include<ceres/ceres.h>


#include<chrono>

using namespace std;

struct CURVE_FITTING_COST{
	CURVE_FITTING_COST( double x, double y): _x(x), _y( y){}
	const double _x,_y;

	template<typename T>
	bool operator()(const T* const abc,T* residual)const{
		//y-exp(ax^2+bc+x)
		residual[0] = T(_y) - ceres::exp(abc[0]*T ( _x)*T( _x)+abc[1]*T( _x)+abc[2]) ;
		return true;
	}
};


int main(int argc, char const *argv[])
{
	//真实参数
	double a=1.0,b=2.0,c=1.0;
	int N=100; //数据点
	double w_sigma=1.0; //噪声的sigma值
	cv::RNG rng; //OpenCV随机数产生器
	double abc[] = {0,0,0}; // abc的参数估计

	vector<double> x_data,y_data; //数据
	cout<<"生成数据:\n";
	for (int i = 0; i < N; i++)
	{
		double x = i/100;
		x_data.push_back(x);
		y_data.push_back(exp(a*pow(x,2)+b*x+c)+rng.gaussian(w_sigma));
		cout<<x_data[i]<<y_data[i]<<endl;
	}

	//构建最小二乘问题
	ceres::Problem problem;
	for (int i = 0; i < N; i++)
	{
		problem.AddResidualBlock( //向问题中添加误差项
			new ceres::AutoDiffCostFunction<CURVE_FITTING_COST,1,3> (new CURVE_FITTING_COST(x_data[i],y_data[i])), 
			nullptr,
			abc //待估计参数
		);
	}

	//配置求解器
	ceres::Solver::Options  options;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout=true;
	
	ceres::Solver::Summary summary; //优化信息
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	ceres::Solve(options,&problem,&summary);
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

	chrono::duration<double> time_used=chrono::duration_cast<chrono::duration<double>>(t2-t1);
	cout<<"花费时间:"<<time_used.count()<<"seconds.\n";

	//输出结果
	cout<<summary.BriefReport()<<endl;
	cout<<"a,b,c的估计值:";
	for(auto a:abc) cout<<a<<" ";
	cout<<endl;

	

	return 0;
}
