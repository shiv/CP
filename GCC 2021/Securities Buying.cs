using System;
using System.Collections.Generic;

class Program {

    static void Main() {

        int k = Convert.ToInt32(Console.ReadLine());
        List<int> numbers = new List<int>(Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse));
        int n = numbers.Count;
        var p = new List<KeyValuePair<int, int>>();
        for (int i = 0; i < n; i++) {
            p.Add(new KeyValuePair<int, int>(i + 1, numbers[i]));
        }

        p.Sort((x, y) => (x.Value.CompareTo(y.Value)));

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (k > 0) {
                int temp = Math.Min(k / p[i].Value, p[i].Key);
                ans += temp;
                k -= temp * p[i].Value;
            }
        }

        Console.WriteLine(ans);
    }
}