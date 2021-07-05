#ifndef GRAPH_MAZE_GENERATOR_HPP_
#define GRAPH_MAZE_GENERATOR_HPP_

#include "node.hpp"
#include <vector>
#include <cstdint>
#include <map>
#include <set>

namespace graph {

struct Vector2D : public std::pair<int, int>
{
	Vector2D(int a, int b) : std::pair<int, int>(a, b) { }
	Vector2D(std::pair<int, int> p) : Vector2D(p.first, p.second) { }

	const int& x() const { return first; }
	const int& y()  const{ return second; }

	int& x() {
		return const_cast<int&>(static_cast<Vector2D const &>(*this).y());
	}
	int& y() {
		return const_cast<int&>(static_cast<Vector2D const &>(*this).y());
	}
};

struct Point2D : public Vector2D
{
	Point2D(int a, int b) : Vector2D(a, b) { }

	Point2D operator+(const Vector2D& v) const {
		return Point2D(this->first + v.first, this->second + v.second);
	}
};

class MazeTile {
public:
	enum Dir {
		N = 1,
		S = 2,
		E = 4,
		W = 8,
	};

	static const std::map<std::pair<int, int>, Dir> Directions;
	static Dir ReverseDir(Dir d);

	void SetConnection(MazeTile& other, Dir d, bool value);
	void Set(Dir d, bool value);
	void Open(Dir d);
	void Close(Dir d);
	bool IsOpen(Dir d) const;

private:
	uint8_t m_dirs;
};

class Maze2D : public graph::Graph<std::pair<int, int>> {

public:
	Maze2D(int width, int height);

	std::list<std::pair<std::pair<int, int>, int>>
		getEdges(const std::pair<int, int>& node) const;

	bool IsInBounds(const Point2D& p);
	bool IsInBounds(int x, int y);
	bool ConnectTiles(const Point2D& p1, const Point2D& p2);
	bool ConnectTiles(int x1, int y1, int x2, int y2);
	bool DisconnectTiles(const Point2D& p1, const Point2D& p2);
	bool DisconnectTiles(int x1, int y1, int x2, int y2);

	int Width() const { return m_width; }
	int Height() const { return m_height; }

	MazeTile& At(const Point2D& p);
	const MazeTile& At(const Point2D& p) const;

private:
	bool TouchConnection(const Point2D& p1, const Point2D& p2, bool value);

	int m_width;
	int m_height;
	std::vector<MazeTile> m_tiles;
};

std::ostream&
operator<<(std::ostream& out, const Maze2D& maze);

class MazeGenerator {
private:
	MazeGenerator() = delete;

public:
	static bool generateMazeImpl(
			Maze2D& maze,
			std::set<Point2D>& visited,
			const Point2D& curr);
	static Maze2D generateMaze(int w, int h);
};

}

#endif  // GRAPH_MAZE_GENERATOR_HPP_

