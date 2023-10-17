#pragma once

#ifndef MANDLEBROT_H_
#define MANDLEBROT_H_
class Mandlebrot
{
public:

	static const int MAX_ITERATIONS = 1000;

	static int getIterations(double x, double y);
};

#endif

