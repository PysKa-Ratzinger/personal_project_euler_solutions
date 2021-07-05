#include "maze_generator.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>

using namespace graph;

const std::map<std::pair<int, int>, MazeTile::Dir>
MazeTile::Directions = {
	{{ 0,  1}, Dir::N},
	{{ 0, -1}, Dir::S},
	{{ 1,  0}, Dir::E},
	{{-1,  0}, Dir::W},
};

MazeTile::Dir MazeTile::ReverseDir(Dir d)
{
	switch (d) {
	case N:
		return Dir::S;
	case S:
		return Dir::N;
	case E:
		return Dir::W;
	case W:
		return Dir::E;
	}
	throw std::runtime_error("Invalid argument");
}

void MazeTile::SetConnection(MazeTile& other, Dir d, bool value)
{
	Set(d, value);
	other.Set(MazeTile::ReverseDir(d), value);
}

void MazeTile::Set(Dir d, bool value)
{
	if (value) {
		Open(d);
	} else {
		Close(d);
	}
}

void MazeTile::Open(Dir d)
{
	m_dirs |= d;
}

void MazeTile::Close(Dir d)
{
	m_dirs &= ~d;
}

bool MazeTile::IsOpen(Dir d) const
{
	return m_dirs & d;
}

Maze2D::Maze2D(int width, int height) :
	m_width(width),
	m_height(height),
	m_tiles(width * height)
{

}

std::list<std::pair<std::pair<int, int>, int>>
	Maze2D::getEdges(const std::pair<int, int>& node) const
{
	int x = node.first;
	int y = node.second;

	std::list<std::pair<std::pair<int, int>, int>> result;

	const MazeTile& t = At(Point2D(x, y));
	for (auto& p : MazeTile::Directions) {
		if (t.IsOpen(p.second)) {
			int px = p.first.first;
			int py = p.first.second;

			auto nPos = std::make_pair(x + px, y + py);
			result.push_back(std::make_pair(nPos, 1));
		}
	}

	return result;
}

bool Maze2D::IsInBounds(const Point2D& p)
{
	return IsInBounds(p.x(), p.y());
}

bool Maze2D::IsInBounds(int x, int y)
{
	return x >= 0 && x < this->m_width
		&& y >= 0 && y < this->m_height;
}

bool Maze2D::ConnectTiles(int x1, int y1, int x2, int y2)
{
	return ConnectTiles(Point2D(x1, y1), Point2D(x2, y2));
}

bool Maze2D::ConnectTiles(const Point2D& p1, const Point2D& p2)
{
	return TouchConnection(p1, p2, true);
}

bool Maze2D::DisconnectTiles(int x1, int y1, int x2, int y2)
{
	return DisconnectTiles(Point2D(x1, y1), Point2D(x2, y2));
}

bool Maze2D::DisconnectTiles(const Point2D& p1, const Point2D& p2)
{
	return TouchConnection(p1, p2, false);
}

std::ostream&
graph::operator<<(std::ostream& out, const Maze2D& maze)
{
	out << "+";
	for (int i=0; i<maze.Width(); i++) {
		out << "--+";
	}
	out << std::endl;

	for (int j=maze.Height()-1; j>=0; j--) {
		out << "|";
		for (int i=0; i<maze.Width(); i++) {
			const MazeTile& t = maze.At(Point2D(i, j));
			if (t.IsOpen(MazeTile::Dir::E)) {
				out << "   ";
			} else {
				out << "  |";
			}
		}
		out << std::endl;

		out << "+";
		for (int i=0; i<maze.Width(); i++) {
			const MazeTile& t = maze.At(Point2D(i, j));
			if (t.IsOpen(MazeTile::Dir::S)) {
				out << "  +";
			} else {
				out << "--+";
			}
		}
		out << std::endl;
	}

	return out;
}

bool Maze2D::TouchConnection(const Point2D& p1, const Point2D& p2, bool value)
{
	if (!IsInBounds(p1) || !IsInBounds(p2))
		return false;

	int x1 = p1.x();
	int x2 = p2.x();
	int y1 = p1.y();
	int y2 = p2.y();

	int diffX = abs(x2-x1);
	int diffY = abs(y2-y1);

	if (diffX > 1 || diffY > 1)
		return false;
	if (diffX == diffY)
		return false;

	MazeTile& t1 = At(p1);
	MazeTile& t2 = At(p2);

	auto dir = std::make_pair(x2-x1, y2-y1);
	t1.SetConnection(t2, MazeTile::Directions.at(dir), value);

	return true;
}

MazeTile& Maze2D::At(const Point2D& p)
{
	return const_cast<MazeTile&>(static_cast<Maze2D const&>(*this).At(p));
}

const MazeTile& Maze2D::At(const Point2D& p) const
{
	return m_tiles.at(p.y() * m_width + p.x());
}

bool MazeGenerator::generateMazeImpl(
		Maze2D& maze,
		std::set<Point2D>& visited,
		const Point2D& curr)
{
	if (visited.find(curr) != visited.end()) {
		return false;
	}

	visited.insert(curr);
	std::vector<std::pair<int, int>> dirs;
	for (auto& p : MazeTile::Directions) {
		dirs.push_back(p.first);
	}
	std::random_shuffle(dirs.begin(), dirs.end());

	for (const auto& p : dirs) {
		Point2D nextP = curr + p;
		if (maze.IsInBounds(nextP) &&
				MazeGenerator::generateMazeImpl(maze, visited, nextP)) {
			maze.ConnectTiles(curr, nextP);
		}
	}

	return true;
}

Maze2D MazeGenerator::generateMaze(int w, int h)
{
	Maze2D result(w, h);
	std::set<Point2D> visited;
	MazeGenerator::generateMazeImpl(result, visited, Point2D(0, 0));
	return result;
}

