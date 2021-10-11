#include<bits/stdc++.h>
using namespace std;

signed main() {
    int n;
    cin >> n;
    int ans = n / 3;
    ans *= 2;
    if (n % 3 == 0) {
        cout << ans;
    }
    else {
        cout << ans + 1;
    }
    return 0;
}

/*
using System;

public class GFG{
    static public void Main (){
        int n = Convert.ToInt32(Console.ReadLine());
        int ans = n / 3;
        ans *= 2;
        if (n % 3 == 0) {
            Console.WriteLine(ans);
        }
        else {
            Console.WriteLine(ans + 1);
        }
    }
}
*/

/*
var stdin_input = "";

process.stdin.on("data", function (input) {
    stdin_input += input;
});

process.stdin.on("end", function () {
   main(stdin_input);
});

function main(input) {
    var n = parseInt(input, 10);
    var ans = Math.floor(n / 3);
    ans *= 2;
    ans += n % 3 != 0;
    console.log(ans);
}
*/