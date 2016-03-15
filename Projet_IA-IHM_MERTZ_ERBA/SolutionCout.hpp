#ifndef SOLUTIONCOUT_HPP_INCLUDED
#define SOLUTIONCOUT_HPP_INCLUDED




template <class S>
class SolutionCout
{ 
public:
	S solution;
	double cout; // cout de solution

	SolutionCout(const S & solution, double(*cout1)(const S & solution)) :solution(solution), cout(cout1(solution)) {}

	const SolutionCout<S> change(const S(*changementAleatoire) (const S & solution), double(*cout1) (const S & solution)) const;

	~SolutionCout();
	operator string() const;
};

template<class S>
SolutionCout<S>::~SolutionCout(){
	solution.~S();
}


template <class S>
ostream & operator << (ostream & os, const SolutionCout<S> & solutionCout)
{
	return os << (string)solutionCout;
}

template <class S>
const SolutionCout<S> SolutionCout<S>::change(const S(*changementAleatoire) (const S & solution), double(*cout1) (const S & solution)) const
{
	return SolutionCout<S>(changementAleatoire(this->solution), cout1);
}

template <class S>
SolutionCout<S>::operator string() const
{
	ostringstream oss;

	oss << "( " << solution << ", " << cout << ")";
	return oss.str();
}

#endif