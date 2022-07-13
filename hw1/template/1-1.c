int main()
{
    int a; b; c; // Store the number of students in classes A, B, and C.

    printf("How many students are in classes A, B, and C, respectively?/n");
    scanf("d% d% d%", a, b, c);

    if(a > b & a > c)
        int max = a;
        printf("Class A has the most students, ");
    if(b > a & b > c)
        int max = b;
        printf("Class B has the most students, ");
    if(c > a & c > b)
        int max = c;
        printf("Class C has the most students, ");
    
    int total = a + b + c;

    // A class can accept at most half of all students. 
    if(max > total / 2)
        printf("and is overly enrolled!/n");
    if(max = total / 2)
        printf("and is full!/n");
    if(max < total / 2)
        printf("and still has open seats!/n");

    return 0;
}
