
//Command line argument $1 $2 $* $#
echo "my name is " $1
echo "i am in " $2 "year"
echo "how you doin"
echo "total no of arguments are " $# " and these are as follows : "
echo $*
echo "name 0f the file is " $0

//Arithmetic operations
echo "enter no 1 :"
read num1
echo "enter no 2 :"
read num2

echo "addition of two no is : " $(( num1 + num2 ))
echo "substraction of two no is : " $(( num1 - num2 ))
echo "multiplication of two no is : " $(( num1 * num2 ))
echo "division of two no is : " $(( num1 / num2 ))
echo "modulus of two no is : " $(( num1 % num2 ))

//If_else
echo "enter no 1 :"
read num1
echo "enter no 2 :"
read num2

if [ $num1 -gt  $num2 ]
then
        echo "num1 is greater than num2"

elif [ $num1 -lt $num2 ]
then
        echo "num2 is greater than num1"

else
        echo "both numbers are same"
fi


// Switch case 
echo "enter from choice 1 2 3"

echo "enter your choice : "
read num
case "$num" in
    #case 1
    "1") echo "user entered 1" ;;

    #case 2
    "2") echo "user entered 2" ;;

    #case 3
    "3") echo "user entered 3" ;;
esac


// for loop
for a in 1 2 3 4 5 6 7 8 9 10
do
    if [ $a == 5 ]
    then
        break
    fi
    echo "Iteration no $a"
done


// Factorial using function
#function for factorial

factorial()
{
        product=$1
        if ((product <= 2));
        then
                echo $product
        else
                f=$((product - 1))

        f=$(factorial $f)
        f=$((f*product))
        echo $f
fi
}

#main program
echo "enter the no : "
read num

if ((num == 0 ));
then
        echo 1
else
        factorial $num
fi


// Array with accending soring
arr=($1 $2 $3 $4 $5)
echo "array in original order"
echo ${arr[*]}

for ((i = 0; i<5; i++))
do
        for (( j = 0; j < 5-i-1; j++))
        do
                if [ ${arr[j]} -gt ${arr[$((j+1))]} ]
                then
                        temp=${arr[j]}
                        arr[$j]=${arr[$(($j+1))]}
                        arr[$((j+1))]=$temp
                fi
        done
done

echo "Array in sorted order : "
echo ${arr[*]}

// Strings

str1="VIT"
echo "String1 = " $str1

read str2
echo "string2 = " $str2

echo "length of the string1 : " ${#str1}

echo "concatenation of strings : " $str1$str2

echo "lowercase of string1 : " ${str1,,}

echo "uppercase of string2 : " ${str2^^}

echo "slicing of string : " ${str1:0:2}

echo "comparing two strings : "

if [ ${#str1} -gt ${#str2} ]
then
echo "string1 is greater than string2"

elif [ ${#str1} -lt ${#str2} ]
then
echo "string2 is greater than string1"

else
echo "both strings are equal"
fi


echo "reverse of the string 2 : "
for ((i=${#str2}-1;i>=0;i--))
do reverse=$reverse${str2:$i:1}
done
echo $reverse

// prime no or not
echo enter a no :
read num
for((i=2; i<=num/2; i++))
do
  if [ $((num%i)) -eq 0 ]
  then
    echo "$num is not a prime number."
    exit
  fi
done
echo "$num is a prime number."

// reverse of a no
echo enter n
read n
num=0
while [ $n -gt 0 ]
do
num=$(expr $num \* 10)
k=$(expr $n % 10)
num=$(expr $num + $k)
n=$(expr $n / 10)
done
echo number is $num

// palindrome or not
num=545

# Storing the remainder
s=0

# Store number in reverse
# order
rev=""

# Store original number
# in another variable
temp=$num

while [ $num -gt 0 ]
do
	# Get Remainder
	s=$(( $num % 10 ))
	
	# Get next digit
	num=$(( $num / 10 ))
	
	# Store previous number and
	# current digit in reverse
	rev=$( echo ${rev}${s} )
done

if [ $temp -eq $rev ];
then
	echo "Number is palindrome"
else
	echo "Number is NOT palindrome"
fi

