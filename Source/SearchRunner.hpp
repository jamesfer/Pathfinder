#ifndef SearchRunner_hpp
#define SearchRunner_hpp

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Searcher.hpp"
#include "BFSSearcher.hpp"
#include "DFSSearcher.hpp"
#include "DijkstraSearcher.hpp"
#include "GreedySearcher.hpp"
#include "AStarSearcher.hpp"
#include "BeamSearcher.hpp"
#include "State.hpp"

using namespace std;


template <class State_type, class HValue_functor, class Success_functor = IsGoalCheck<State_type>>
class SearchRunner
{
public:
	typedef shared_ptr<Searcher<State_type, Success_functor>> Searcher_ptr;

private:
	/**
	 * Vector of identifiers to available search classes
	 */
	map<string, Searcher_ptr> searchers;

public:
	/**
	 * Creates an instance of each kind of searcher
	 */
	SearchRunner(HValue_functor func = HValue_functor(), Success_functor successCheck = Success_functor())
	{
		// Populate the array of searchers
		searchers["BFS"] = make_shared<BFSSearcher<State_type, Success_functor>>(successCheck);
		searchers["DFS"] = make_shared<DFSSearcher<State_type, Success_functor>>(successCheck);
		searchers["CUS1"] = make_shared<DijkstraSearcher<State_type, Success_functor>>(successCheck);

		searchers["GBFS"] = make_shared<GreedySearcher<State_type, HValue_functor, Success_functor>>(func, successCheck);
		searchers["AS"] = make_shared<AStarSearcher<State_type, HValue_functor, Success_functor>>(func, successCheck);
		searchers["CUS2"] = make_shared<BeamSearcher<State_type, HValue_functor, Success_functor>>(func, successCheck);
	}


	/**
	 * Performs a search using the given searcher object.
	 * Only enabled when the success functor is of the IsGoalCheck type.
	 */
	template <class T = Success_functor, typename = typename enable_if<is_same<T, IsGoalCheck<State_type>>::value>::type>
	void searchUsing(Searcher_ptr searcher, string searcherName, const State_type& initial, const State_type& goal)
	{
		cout << searcherName << " ";

		try
		{
			shared_ptr<Path<State_type>> path = searcher->search(initial, goal);

			cout << searcher->getNodeCount() << " " << *path << endl;
			searcher->reset();
		}
		catch (...)
		{
			cout << searcher->getNodeCount() << " " << "No solution found" << endl;
		}
	}


	/**
	 * Performs a search with every available searcher.
	 * Only enabled when the success functor is of the IsGoalCheck type.
	 */
	template <class T = Success_functor, typename = typename enable_if<is_same<T, IsGoalCheck<State_type>>::value>::type>
	void searchAll(const State_type& initial, const State_type& goal)
	{
		for (typename map<string, Searcher_ptr>::iterator it = searchers.begin(); it != searchers.end(); ++it)
		{
			searchUsing((*it).second, (*it).first, initial, goal);
		}
	}


	/**
	 * Performs a search using a single searcher that matches the given name.
	 * Only enabled when the success functor is of the IsGoalCheck type.
	 */
	template <class T = Success_functor, typename = typename enable_if<is_same<T, IsGoalCheck<State_type>>::value>::type>
	void search(const State_type& initial, const State_type& goal, string searchName)
	{
		try
		{
			Searcher_ptr searcher = searchers.at(searchName);
			searchUsing(searcher, searchName, initial, goal);
		}
		catch (out_of_range e)
		{
			cout << "That name does not match any known searchers" << endl;
		}
	}


	/**
	 * Performs a search using the given searcher object.
	 * Only enabled when the success functor is not of the IsGoalCheck type.
	 */
	template <class T = Success_functor, typename = typename enable_if<!is_same<T, IsGoalCheck<State_type>>::value>::type>
	void searchUsing(Searcher_ptr searcher, string searcherName, const State_type& initial)
	{
		cout << searcherName << " ";

		try
		{
			shared_ptr<Path<State_type>> path = searcher->search(initial);

			cout << searcher->getNodeCount() << " " << *path << endl;
			searcher->reset();
		}
		catch (...)
		{
			cout << searcher->getNodeCount() << " " << "No solution found" << endl;
		}
	}


	/**
	 * Performs a search with every available searcher.
	 * Only enabled when the success functor is not of the IsGoalCheck type.
	 */
	template <class T = Success_functor, typename = typename enable_if<!is_same<T, IsGoalCheck<State_type>>::value>::type>
	void searchAll(const State_type& initial)
	{
		for (typename map<string, Searcher_ptr>::iterator it = searchers.begin(); it != searchers.end(); ++it)
		{
			searchUsing((*it).second, (*it).first, initial);
		}
	}


	/**
	 * Performs a search using a single searcher that matches the given name.
	 * Only enabled when the success functor is not of the IsGoalCheck type.
	 */
	template <class T = Success_functor, typename = typename enable_if<!is_same<T, IsGoalCheck<State_type>>::value>::type>
	void search(const State_type& initial, string searchName) noexcept
	{
		try
		{
			Searcher_ptr searcher = searchers.at(searchName);
			searchUsing(searcher, searchName, initial);
		}
		catch (out_of_range e)
		{
			cout << "That name does not match any known searchers" << endl;
		}
	}
};

#endif /* SearchRunner_hpp */
