// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=36

var threeNPlusOne = function(n)
{
	var iters = 1;

	while (n > 1)
	{
		iters++;

		if (n % 2)
		{
			n = 3*n + 1;
		}
		else
		{
			n = n >> 1;
		}
	}
	return iters;
};

var maxIters = function(o, p)
{
	if (o > p)
	{
		var tmp = o;
		o = p;
		p = tmp;
	}

	var max = 0;
	var current;

	for ( ; o <= p; o++)
	{
		current = threeNPlusOne(o);

		if (current > max)
		{
			max = current;
		}
	}

	return max;
};

var solve = function(o, p)
{
	var solution = maxIters(o, p);
	console.log(o + ' ' + p + ' ' + solution);
};

solve(1, 10);
solve(10, 200);
solve(201, 210);
solve(900, 1000);
