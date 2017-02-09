var printArray = function(a)
{
	for (ai = 0; ai < a.length; ai++)
		console.log(a[ai]);
};

var eratosthenes = function(n) {
    // Eratosthenes algorithm to find all primes under n
    var array = [], upperLimit = Math.sqrt(n), output = [];

    // Make an array from 2 to (n - 1)
    for (i = 0; i < n; i++) {
        array[i] = true;
    }
    //console.log(upperLimit); printArray(array);
	
    // Remove multiples of primes starting from 2, 3, 5,...
    for (i = 2; i <= upperLimit; i++) {
        if (array[i]) {
            for (j = i * i; j < n; j = j + i) {
                array[j] = false;
            }
        }
    }
    //console.log(''); printArray(array);	

    // All array[i] set to true are primes
    for (i = 2; i < n; i++) {
        if (array[i]) {
            output[output.length] = i;
        }
    }

    return output;
};

var N = 1000*1000;
var output = eratosthenes(N);
printArray(output);
console.log('Prime numbers between 2 and ' + N + ' = ' + output.length);

