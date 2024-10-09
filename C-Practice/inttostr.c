//Int to str - JJ (I just need to be able to get this)

void intToStr(char *str, int num){
	char *tempStr;
	int i = 0;
	while(num != 0){
		tempStr[i] = (num%10) + '0'; //Convert to character by adding 0
		num = num/10;
		i++;
	}
	//Num is now converted to str, however it is backwards. Must convert back
	int max = i, j = 0;
	while(j <= max){
		str[j] = tempStr[i];
		j++;
		i--;
	}

	str[max+1] = '\0' //Escape character for string
	return str;
}
