#include "../include/convexHulls.hpp"

using namespace std;
using namespace DGtal;

typedef PointVector<2,DGtal::int32_t> Point;

/**
* Random stuff
**/

class RandomEngine
{
	public:
		RandomEngine(unsigned int n);
		~RandomEngine() {};

		unsigned int sample();

	private:
		std::default_random_engine m_engine;
		std::uniform_real_distribution<double> m_distrib;
};

RandomEngine::RandomEngine(unsigned int n) : m_engine(default_random_engine()), m_distrib(uniform_real_distribution<double>(0,n+1)) {}

unsigned int RandomEngine::sample()
{
	double d = m_distrib(m_engine);
	return static_cast<unsigned int>(floor(d));	
}

vector<Point> randomSet(RandomEngine& eng, unsigned int t)
{
	vector<Point> set;
    for (unsigned int i = 0; i < t; i++)
	{
		unsigned int x = eng.sample();
		unsigned int y = eng.sample();
		set.push_back(Point(x,y));
	}
	return set;
}

/**
* The statistics I did
**/

void doStatistics(unsigned int n, unsigned int t, unsigned int nb_exp, ostream& s)
{
	RandomEngine eng(n);
	for (unsigned int i = 0; i < nb_exp; i++)
	{
		vector<Point> set = randomSet(eng, t);
		vector<vector<Point>> res = getLayers(set);
		unsigned int nb_layers = res.size();
		unsigned int monomials = 0;
		for (unsigned int j = 0; j < nb_layers;j++)
			monomials += res[j].size();
		s << monomials << "," << nb_layers << endl;
}	}   

int main(int argc, char** argv) {
	unsigned int n = 200;
	vector<unsigned int> t_values = {10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,230,260,290,320};
	ofstream file("values.csv");
	if (file.is_open())
	{
		file << "nb of monomials, nb layers" << endl; 
		for (unsigned int i = 0; i != t_values.size(); i++)
		{
			unsigned int t = t_values[i];
			cout << "Processing t = " << t << endl;
			doStatistics(n,t,5*t,file);
	}	}

	return EXIT_SUCCESS;
}
