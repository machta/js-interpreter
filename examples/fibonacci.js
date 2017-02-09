var N = 30;
var array = [];

var fib = function(n)
{
	if (n <= 2)
		return 1;
	return fib(n - 2) + fib(n - 1);
};

var fib2Rec = function(n)
{
	if (array[n] > 0)
		return array[n];
		
	var result =  fib2Rec(n - 2) + fib2Rec(n - 1);
	array[n] = result;
	return result;
};

var fib2 = function(n)
{
	array = [1, 1, 1];
	return fib2Rec(n);
};

var fib3 = function(n)
{
	if (n <= 2)
		return 1;
		
	array[0] = 1;
	array[1] = 1;	
	for (j = 3; j <= n; j++)
	{
		var tmp = array[0] + array[1];
		array[0] = array[1];
		array[1] = tmp;
	}
	return array[1];
};

var print = function(fun, name)
{
	for (i = 1; i < N; i++)
	{
		console.log('  ' + name + '(' + i + ') = ' + fun(i));
	}
};

console.log('Recursive:');
print(fib, 'fib');
console.log('');

console.log('Dynamic programming:');
print(fib2, 'fib2');
console.log('');

console.log('Optimal:');
print(fib3, 'fib3');
console.log('');

