# LeeCode

## 1. Two Sum

### 1.1 Description

Given an array of integers, return indices of the two numbers such that they add up to a specific target. You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

	Given nums = [2, 7, 11, 15], target = 9,
	Because nums[0] + nums[1] = 2 + 7 = 9,
	return [0, 1].

### 1.2 Analysis

这道题给了我们一个数组，还有一个目标数target，让找到两个数字，使其和为 target，乍一看就感觉可以用暴力搜索，但是猜到 OJ 肯定不会允许用暴力搜索这么简单的方法，于是去试了一下，果然是 Time Limit Exceeded，这个算法的时间复杂度是 O(n^2)。那么只能想个 O(n) 的算法来实现，由于暴力搜索的方法是遍历所有的两个数字的组合，然后算其和，这样虽然节省了空间，但是时间复杂度高。一般来说，为了提高时间的复杂度，需要用空间来换，这算是一个 trade off 吧，但这里只想用线性的时间复杂度来解决问题，就是说只能遍历一个数字，那么另一个数字呢，可以事先将其存储起来，使用一个 HashMap，来建立数字和其坐标位置之间的映射，由于 HashMap 是常数级的查找效率，这样在遍历数组的时候，用 target 减去遍历到的数字，就是另一个需要的数字了，直接在 HashMap 中查找其是否存在即可，注意要判断查找到的数字不是第一个数字，比如 target 是4，遍历到了一个2，那么另外一个2不能是之前那个2，整个实现步骤为：先遍历一遍数组，建立 HashMap 映射，然后再遍历一遍，开始查找，找到则记录 index。

### 1.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <unordered_map>
	using namespace std;

	vector<int> two_sum(vector<int> &nums, int target)
	{
		unordered_map<int, int> m;
		vector<int> res;

		for (int i = 0; i < nums.size(); i++) {
			m[nums[i]] = i;
		}

		for (int i = 0; i < nums.size();i++) {
			int t = target - nums[i];
			if (m.count(t) && m[t] != i) {
				res.push_back(i);
				res.push_back(m[t]);
				break;
			}
		}
		return res;
	}

	//测试程序
	int main()
	{	
		vector<int> a = {2, 7, 11, 15};
		int target = 9;
		vector<int> b = two_sum(a, target);
		for (int i = 0; i < b.size(); i++) {
			cout << b[i] << " ";
		}
		cout << endl;
	}

**2.Solution 2**

	vector<int> two_sum(vector<int> &nums, int target)
	{
		unordered_map<int, int> m;
		for (int i = 0; i < nums.size(); i++) {
			if (m.count(target - nums[i])) {
				return {m[target - nums[i]], i};
			}
			m[nums[i]] = i;
		}
	}

## 2. Add Two Number

### 2.1 Description

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

	Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output: 7 -> 0 -> 8
	Explanation: 342 + 465 = 807.

### 2.2 Analysis

这道并不是什么难题，算法很简单，链表的数据类型也不难，就是建立一个新链表，然后把输入的两个链表从头往后撸，每两个相加，添加一个新节点到新链表后面。为了避免两个输入链表同时为空，我们建立一个 dummy 结点，将两个结点相加生成的新结点按顺序加到 dummy 结点之后，由于 dummy 结点本身不能变，所以用一个指针 cur 来指向新链表的最后一个结点。好，可以开始让两个链表相加了，这道题好就好在最低位在链表的开头，所以可以在遍历链表的同时按从低到高的顺序直接相加。while 循环的条件两个链表中只要有一个不为空行，由于链表可能为空，所以在取当前结点值的时候，先判断一下，若为空则取0，否则取结点值。然后把两个结点值相加，同时还要加上进位 carry。然后更新 carry，直接 sum/10 即可，然后以 sum%10 为值建立一个新结点，连到 cur 后面，然后 cur 移动到下一个结点。之后再更新两个结点，若存在，则指向下一个位置。while 循环退出之后，最高位的进位问题要最后特殊处理一下，若 carry 为1，则再建一个值为1的结点。

### 2.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	struct list_node {
		int val;
		list_node *next;
		list_node(int v) :
			val(v),
			next(nullptr)
		{}
	};

	list_node *add_two_numbers(list_node *l1, list_node *l2)
	{
		list_node *dummp = new list_node(-1), *cur = dummy;
		int carry = 0;
		while (l1 || l2) {
			int val1 = l1 ? l1->val : 0;
			int val2 = l2 ? l2->val : 0;
			int sum = val1 + val2 + carry;
			carry = sum / 10;
			cur->next = new list_node(sum % 10);
			cur = cur->next;
			l1 = l1->next;
			l2 = l2->next;
		}
		if (carry)
			cur->next = new list_node(1);
		return dummy->next;
	}

	//测试程序
	int main()
	{
		list_node *l1 = new list_node(2);
		list_node *l2 = new list_node(5);
		list_node *res;
	
		list_node *cur = l1;
	
		cur->next = new list_node(4);
		cur = cur->next;
		cur->next = new list_node(5);
	
		cur = l2;
		cur->next = new list_node(6);
		cur = cur->next;
		cur->next = new list_node(4);
	
		res = add_two_numbers(l1, l2);
		while (res) {
			cout << res->val << " ";
			res = res->next;
		}
	}
	//结果为: 7 0 0 1

**2.Solution 2**

正序情况如下:Suppose the digits are stored in forward order. Repeat the above problem.
	
	EXAMPLE--->此时输入的数据是高位在前,低位在后.
	Input: (6 -> 1 -> 7) + (2 -> 9 -> 5).That is, 617 + 295.
	Output: 9 -> 1 -> 2.That is, 912.

方法为将链表翻转下,再用之前的方法完成相加.代码如下:

	list_node *reverse_list(list_node *head)
	{
		if (!head)
			return head;

		list_node *dummy = new list_node(-1);
		dummy->next = head;
		list_node *cur = head;
		if (cur->next) {
			list_node *tmp = cur->next;
			cur->next = tmp->next;
			tmp->next = dummy->next;
			dummy->next = tmp;
		}
		return dummy->next;		
	}

## 3. Longest Substring Without Repeating Characters

### 3.1 Description

Given a string, find the length of the longest substring without repeating characters.

Example 1:

	Input: "abcabcbb"
	Output: 3 
	Explanation: The answer is "abc", with the length of 3.

Example 2:

	Input: "bbbbb"
	Output: 1
	Explanation: The answer is "b", with the length of 1.

Example 3:

	Input: "pwwkew"
	Output: 3
	Explanation: The answer is "wke", with the length of 3.

### 3.2 Analysis

先不考虑代码怎么实现，如果给一个例子中的例子 "abcabcbb"，让你手动找无重复字符的子串，该怎么找。博主会一个字符一个字符的遍历，比如 a，b，c，然后又出现了一个a，那么此时就应该去掉第一次出现的a，然后继续往后，又出现了一个b，则应该去掉一次出现的b，以此类推，最终发现最长的长度为3。所以说，需要记录之前出现过的字符，记录的方式有很多，最常见的是统计字符出现的个数，但是这道题字符出现的位置很重要，所以可以使用 HashMap 来建立字符和其出现位置之间的映射。进一步考虑，由于字符会重复出现，到底是保存所有出现的位置呢，还是只记录一个位置？我们之前手动推导的方法实际上是维护了一个滑动窗口，窗口内的都是没有重复的字符，需要尽可能的扩大窗口的大小。由于窗口在不停向右滑动，所以只关心每个字符最后出现的位置，并建立映射。窗口的右边界就是当前遍历到的字符的位置，为了求出窗口的大小，需要一个变量 left 来指向滑动窗口的左边界，这样，如果当前遍历到的字符从未出现过，那么直接扩大右边界，如果之前出现过，那么就分两种情况，在或不在滑动窗口内，如果不在滑动窗口内，那么就没事，当前字符可以加进来，如果在的话，就需要先在滑动窗口内去掉这个已经出现过的字符了，去掉的方法并不需要将左边界 left 一位一位向右遍历查找，由于 HashMap 已经保存了该重复字符最后出现的位置，所以直接移动 left 指针就可以了。维护一个结果 res，每次用出现过的窗口大小来更新结果 res，就可以得到最终结果啦。

这里可以建立一个 HashMap，建立每个字符和其最后出现位置之间的映射，然后需要定义两个变量 res 和 left，其中 res 用来记录最长无重复子串的长度，left 指向该无重复子串左边的起始位置的前一个，由于是前一个，所以初始化就是 -1，然后遍历整个字符串，对于每一个遍历到的字符，如果该字符已经在 HashMap 中存在了，并且如果其映射值大于 left 的话，那么更新 left 为当前映射值。然后映射值更新为当前坐标i，这样保证了 left 始终为当前边界的前一个位置，然后计算窗口长度的时候，直接用 i-left 即可，用来更新结果 res。

### 3.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	#include <algorithm>
	#include <unordered_map>
	using namespace std;

	int length_of_longest_substring(string s)
	{
		int res = 0, left = -1, n = s.size();
		unordered_map<int, int> m;
		
		for (int i = 0; i < n; i++) {
			if (m.count(s[i]) && m[s[i]] > left) {
				left = m[s[i]];
			}
			m[s[i]] = i;
			res = max(res, i - left);
		}
		return res;
	}

	//测试程序
	int main()
	{
		string s = "pwwkew";
		cout << length_of_longest_substring(s) << endl;	//结果为3.
	}

代码结构分析:程序中那个 if 条件语句中的两个条件 m.count(s[i]) && m[s[i]] > left，因为一旦当前字符 s[i] 在 HashMap 已经存在映射，说明当前的字符已经出现过了，而若 m[s[i]] > left 成立，说明之前出现过的字符在窗口内，那么如果要加上当前这个重复的字符，就要移除之前的那个，所以让 left 赋值为 m[s[i]]，由于 left 是窗口左边界的前一个位置（这也是 left 初始化为 -1 的原因，因为窗口左边界是从0开始遍历的），所以相当于已经移除出滑动窗口了。举一个最简单的例子 "aa"，当 i=0 时，建立了 a->0 的映射，并且此时结果 res 更新为1，那么当 i=1 的时候，发现a在 HashMap 中，并且映射值0大于 left 的 -1，所以此时 left 更新为0，映射对更新为 a->1，那么此时 i-left 还为1，不用更新结果 res，那么最终结果 res 还为1。

**2.Solution 2**

下面这种写法是上面解法的精简模式，这里我们可以建立一个 256 位大小的整型数组来代替 HashMap，这样做的原因是 ASCII 表共能表示 256 个字符，但是由于键盘只能表示 128 个字符，所以用 128 也行，然后全部初始化为 -1，这样的好处是不用像之前的 HashMap 一样要查找当前字符是否存在映射对了，对于每一个遍历到的字符，直接用其在数组中的值来更新 left，因为默认是 -1，而 left 初始化也是 -1，所以并不会产生错误，这样就省了 if 判断的步骤，其余思路都一样。

	#include <iostream>
	#include <algorithm>
	#include <vector>
	using namespace std;

	int length_of_longest_substring(string s)
	{
		int res = 0, left = -1, n = s.size();
		vector<int> m(128, -1);
		for (int i = 0; i < n; i++) {
			left = max(left, m[s[i]]);	//因为全部初始化为-1
			m[s[i]] = i;
			res = max(res, i - left);
		}
		return res;
	}

## 4. Median of Two Sorted Arrays

### 4.1 Description

## 5. Longest Palindromic Substring

### 5.1 Description

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:
	
	Input: "babad"
	Output: "bab"
	Note: "aba" is also a valid answer.

Example 2:

	Input: "cbbd"
	Output: "bb"

### 5.2 Analysis

什么是回文串，就是正读反读都一样的字符串，比如 "bob", "level", "noon" 等等。那么最长回文子串就是在一个字符串中的那个最长的回文子串。

LeetCode 中关于回文串的题共有五道，除了这道，其他的四道为 Palindrome Number，Validate Palindrome，Palindrome Partitioning，Palindrome Partitioning II，我们知道传统的验证回文串的方法就是两个两个的对称验证是否相等，那么对于找回文字串的问题，就要以每一个字符为中心，像两边扩散来寻找回文串，这个算法的时间复杂度是 O(n*n)，可以通过 OJ，就是要注意奇偶情况，由于回文串的长度可奇可偶，比如 "bob" 是奇数形式的回文，"noon" 就是偶数形式的回文，两种形式的回文都要搜索，对于奇数形式的，我们就从遍历到的位置为中心，向两边进行扩散，对于偶数情况，我们就把当前位置和下一个位置当作偶数行回文的最中间两个字符，然后向两边进行搜索。

### 5.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	using namespace std;
	
	void search_palindrome(string s, int left, int right, int &start, int &max_len)
	{
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			left--;
			right++;
		}

		if (max_len < right - left - 1) {
			start = left + 1;
			max_len = right - left - 1;
		}
	}

	string longest_palindrome(string s)
	{
		if (s.size() < 2)
			return s;
		int n = s.size(), start = 0, max_len = 0;
		for (int i = 0; i < n - 1; i++) {
			search_palindrome(s, i, i, start, max_len);
			search_palindrome(s, i, i + 1, start, max_len);
		}
		return s.substr(start, max_len);
	}

	//测试程序
	int main()
	{
		string s = "babad";
		string res = longest_palindrome(s);
		cout << res << endl;	//结果为:bab
	}

**2.Solution 2**

我们也可以不使用子函数，直接在一个函数中搞定，我们还是要定义两个变量 start 和 maxLen，分别表示最长回文子串的起点跟长度，在遍历s中的字符的时候，我们首先判断剩余的字符数是否小于等于 maxLen 的一半，是的话表明就算从当前到末尾到子串是半个回文串，那么整个回文串长度最多也就是 maxLen，既然 maxLen 无法再变长了，计算这些就没有意义，直接在当前位置 break 掉就行了。否则就要继续判断，我们用两个变量 left 和 right 分别指向当前位置，然后我们先要做的是向右遍历跳过重复项，这个操作很必要，比如对于 noon，i在第一个o的位置，如果我们以o为最中心往两边扩散，是无法得到长度为4的回文串的，只有先跳过重复，此时left指向第一个o，right指向第二个o，然后再向两边扩散。而对于 bob，i在第一个o的位置时，无法向右跳过重复，此时 left 和 right 同时指向o，再向两边扩散也是正确的，所以可以同时处理奇数和偶数的回文串，之后的操作就是更新 maxLen 和 start 了，跟上面的操作一样。

	string longest_palindrome(string s)
	{
		if (s.size() < 2)
			return s;
		int n = s.size(), start = 0, max_len = 0;
		for (int i = 0; i < n;) {
			if ((n - i) <= (max_len / 2))
				break;
			int left = i, right = i;
			while (right < n - 1 && s[right + 1] == s[right]) {
				right++;
			}
			i = right + 1;
			while (right < n - 1 && left > 0 && s[right + 1] == s[left - 1]) {
				right++;
				left--;
			}
			if (max_len < right - left + 1) {
				start = left;
				max_len = right - left + 1;
			}
		}
		return s.substr(start, max_len);
	}

**3.Solution 3**

[还有一种使用马拉车算法 Manacher's Algorithm](https://github.com/grandyang/leetcode/issues/5)

	马拉车算法将时间复杂度提升到了 O(n) 这种逆天的地步，而算法本身也设计的很巧妙。暂时没看。

[Manacher's Algorithm 马拉车算法介绍](https://www.cnblogs.com/grandyang/p/4475985.html)

## 6. ZigZag Conversion

### 6.1 Description

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility).

	P   A   H   N
	A P L S I I G
	Y   I   R

### 6.2 Analysis

上述理解起来比较苦难，简单理解为就是要把字符串摆成一个之字型的，比如有一个字符串 "0123456789ABCDEF"，转为 zigzag 如下所示：

	当 n = 2 时：
	0 2 4 6 8 A C E
	1 3 5 7 9 B D F
	当 n = 3 时：
	0    4    8    C
	1 3  5 7  9 B  D F		//此行中的"3, 7, B, F"为红色元素
	2    6    A    E
	当 n = 4 时：
	0    6     C
	1 5  7 B   D	//此行中的"5, B"为红色元素
	2 4  8 A   E	//此行中的"4, A"为红色元素
	3    9     F

可以发现，除了第一行和最后一行没有中间形成之字型的数字外，其他都有，而首位两行中相邻两个元素的 index 之差跟行数是相关的，为  2*nRows - 2, 根据这个特点，可以按顺序找到所有的黑色元素在元字符串的位置，将他们按顺序加到新字符串里面。对于红色元素出现的位置也是有规律的，每个红色元素的位置为 j + 2 x numRows-2 - 2 x i, 其中，j为前一个黑色元素的列数，i为当前行数。 比如当 n = 4 中的那个红色5，它的位置为 1 + 2 x 4-2 - 2 x 1 = 5，为原字符串的正确位置。知道了所有黑色元素和红色元素位置的正确算法，就可以一次性的把它们按顺序都加到新的字符串里面。

### 6.3 Code

**1.Solution**

	#include <iostream>
	#include <string>
	using namespace std;

	string convert(string s, int num_rows)
	{
		if (num_rows <= 1)
			return s;

		string res;
		int step = 2 * num_rows - 2, n = s.size();

		for (int i = 0; i < num_rows; i++) {
			for (int j = i; j < n; j += step) {
				res += s[j];
				int pos = j + step - 2 * i;
				if (i != 0 && i != num_rows - 1 && pos < n)
					res += s[pos];
			}
		}
		return res;
	}

	//测试程序
	int main()
	{
		string s = "0123456789ABCDEF";
		string s1 = convert(s, 2);
		string s2 = convert(s, 3);
		string s3 = convert(s, 4);
		cout << s1 << "---" << s2 << "---" << s3 << endl;
	}
	//结果为:02468ACE13579BDF---048C13579BDF26AE---06C157BD248AE39F

## 7. Reverse Integer

### 7.1 Description

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

	Input: 123
	Output: 321

Example 2:

	Input: -123
	Output: -321

Example 3:

	Input: 120
	Output: 21

### 7.2 Analysis

翻转数字问题需要注意的就是溢出问题，由于int型的数值范围是 -2147483648～2147483647，那么如果要翻转 1000000009 这个在范围内的数得到 9000000001，而翻转后的数就超过了范围。

### 7.3 Code

**1.Solution**

	#include <iostream>
	using namespace std;

	int reverse(int x)
	{
		int res = 0;
		while (x != 0) {
			if (abs(res) > INT_MAX / 10)	// INT_MAX为:2147483647
				return 0;
			res = res * 10 + x % 10;
			x = x / 10;
		}
		return res;
	}
	//测试程序
	int main()
	{
		int x = -1463847412;
		cout << reverse(x) << endl;
	}

在贴出答案的同时，OJ 还提了一个问题 To check for overflow/underflow, we could check if ret > 214748364 or ret < –214748364 before multiplying by 10. On the other hand, we do not need to check if ret == 214748364, why? （214748364 即为 INT_MAX / 10）。为什么不用 check 是否等于 214748364 呢，因为输入的x也是一个整型数，所以x的范围也应该在 -2147483648～2147483647 之间，那么x的第一位只能是1或者2，翻转之后 res 的最后一位只能是1或2，所以 res 只能是 2147483641 或 2147483642 都在 int 的范围内。但是它们对应的x为 1463847412 和 2463847412，后者超出了数值范围。所以当过程中 res 等于 214748364 时， 输入的x只能为 1463847412， 翻转后的结果为 2147483641，都在正确的范围内，所以不用 check。

## 8. String to Integer

### 8.1 Description

Example 1:

	Input: "42"
	Output: 42

Example 2:

	Input: "   -42"
	Output: -42
	Explanation: The first non-whitespace character is '-', which is the minus sign.
	             Then take as many numerical digits as possible, which gets 42.

Example 3:

	Input: "4193 with words"
	Output: 4193

Example 4:

	Input: "words and 987"
	Output: 0
	Explanation: The first non-whitespace character is 'w', which is not a numerical 
	             digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:

	Input: "-91283472332"
	Output: -2147483648
	Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
	             Thefore INT_MIN (−231) is returned.

### 8.2 Analysis

字符串转为整数是很常用的一个函数，由于输入的是字符串，所以需要考虑的情况有很多种。这题只需要考虑数字和符号的情况：
	
	1.若字符串开头是空格，则跳过所有空格，到第一个非空格字符，如果没有，则返回0.
	2.若第一个非空格字符是符号 +/-，则标记 sign 的真假，这道题还有个局限性，那就是在 c++ 里面，
		+-1 和-+1 都是认可的，都是 -1，而在此题里，则会返回0.
	3.若下一个字符不是数字，则返回0，完全不考虑小数点和自然数的情况，不过这样也好，起码省事了不少。
	4.如果下一个字符是数字，则转为整形存下来，若接下来再有非数字出现，则返回目前的结果。
	5.还需要考虑边界问题，如果超过了整型数的范围，则用边界值替代当前值。

### 8.3 Code

**1.Solution**

	#include <iostream>
	#include <string>
	using namespace std;

	int my_atoi(string s)
	{
		if (s.empty())
			return 0;
		int sign = 1, base = 0, i = 0, n = s.size();
		while (i < n && s[i] == ' ') {
			i++;
		}
		if (i < n && (s[i] == '+' || s[i] == '-')) {
			sign = (s[i++] == '+') ? 1 : -1;
		}
		while (i < n && (s[i] >= '0' && s[i] <= '9')) {
			if ((base > INT_MAX / 10) || (base == INT_MAX && s[i] > '7')) {
				return (sign == 1) : INT_MAX : INT_MIN;
			}
			base = base * 10 + (s[i++] - '0');
		}
		return base * sign;
	}
	//测试程序
	int main()
	{
		cout << my_atoi("4193 with words") << endl;	//结果为:4193
		//cout << typeid(to_string(1234)).name() << endl;
		/*
			to_string(1234)--->将数组转换为字符串
			typeid(to_string(1234)).name():查看类型
		*/
	}

## 9. Palindrome Number

### 9.1 Description

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

	Input: 121
	Output: true

Example 2:

	Input: -121
	Output: false

### 9.2 Analysis

直接对整数进行操作，可以利用取整和取余来获得想要的数字，比如 1221 这个数字，如果 计算 1221 / 1000， 则可得首位1，如果 1221 % 10， 则可得到末尾1，进行比较，然后把中间的 22 取出继续比较。

### 9.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	bool is_palindrome(int x)
	{
		if (x < 0)
			return false;

		int div = 1;
		while (x / div >= 10)
			div *= 10;
		while (x > 0) {
			int left = x / div;
			int right = x % 10;
			if (left != right)
				return false;
			x = (x % div) / 10;
			div /= 100;
		}
		return true;
	}
	//测试程序
	int main()
	{
		cout << boolalpha << is_palindrome(123321) << endl;
	}

**2.Solution 2**

一种很巧妙的解法，还是首先判断x是否为负数，这里可以用一个小 trick，因为整数的最高位不能是0，所以回文数的最低位也不能为0，数字0除外，所以如果发现某个正数的末尾是0了，也直接返回 false 即可。好，下面来看具体解法，要验证回文数，那么就需要看前后半段是否对称，如果把后半段翻转一下，就看和前半段是否相等就行了。所以做法就是取出后半段数字，进行翻转，具体做法是，每次通过对 10 取余，取出最低位的数字，然后加到取出数的末尾，就是将 revertNum 乘以 10，再加上这个余数，这样翻转也就同时完成了，每取一个最低位数字，x都要自除以 10。这样当 revertNum 大于等于x的时候循环停止。由于回文数的位数可奇可偶，如果是偶数的话，那么 revertNum 就应该和x相等了；如果是奇数的话，那么最中间的数字就在 revertNum 的最低位上了，除以 10 以后应该和x是相等的。

	bool is_palindrome(int x)
	{
		if (x < 0 || (x != 0 && x % 10 == 0))
			return false;
		int reverse_num = 0;
		while (x > reverse_num) {
			reverse_num = reverse_num * 10 + x % 10;
			x = x / 10;
		}
		return x == reverse_num || x == reverse_num / 10;
	}

## 10. Regular Expression Matching

### 10.1 Description

### 10.2 Analysis

### 10.3 Code

## 11. Container With Most Water

### 11.1 Description

Given n non-negative integers  a1 ,  a2 , ...,  an , where each represents a point at coordinate ( i ,  ai ).  n  vertical lines are drawn such that the two endpoints of line  i  is at ( i ,  ai ) and ( i , 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
Note: You may not slant the container and  n is at least 2.

![](images/container_with_most_water.png)

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

Example:

	Input: [1,8,6,2,5,4,8,3,7]
	Output: 49

### 11.2 Analysis

定义i和j两个指针分别指向数组的左右两端，然后两个指针向中间搜索，每移动一次算一个值和结果比较取较大的，容器装水量的算法是找出左右两个边缘中较小的那个乘以两边缘的距离。

### 11.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <algorithm>
	using namespace std;

	int max_area(vector<int> height)
	{
		int res = 0, i = 0, j = height.size() - 1;
		while (i < j) {
			res = max(res, min(height[i], height[j]) * (j - i));
			(height[i] < height[j]) ? i++ : j--; 
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> height = {1,8,6,2,5,4,8,3,7};
		cout << max_area(height) << endl;
	}

**2.Solution 2**

	int max_area(vector<int> height)
	{
		int res = 0, i = 0, j = height.size() - 1;
		while (i < j) {
			int h = min(height[i], height[j]);
			res = max(res, h * (j - i));
			while (i < j && h == height[i])
				i++;
			while (i < j && h == height[j])
				j++;
		}
		return res;
	}

## 12. Integer to Roman

### 12.1 Description

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

	Symbol       Value
	I             1
	V             5
	X             10
	L             50
	C             100
	D             500
	M             1000

Example 1:

	Input: 9
	Output: "IX"

Example 2:

	Input: 58
	Output: "LVIII"
	Explanation: L = 50, V = 5, III = 3.

Example 3:

	Input: 1994
	Output: "MCMXCIV"
	Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

### 12.2 Analysis

整数 1437 的罗马数字为 MCDXXXVII， 我们不难发现，千位，百位，十位和个位上的数分别用罗马数字表示了。 1000 - M, 400 - CD, 30 - XXX, 7 - VII。所以我们要做的就是用取商法分别提取各个位上的数字，然后分别表示出来：

	100 - C
	200 - CC
	300 - CCC
	400 - CD
	500 - D
	600 - DC
	700 - DCC
	800 - DCCC
	900 - CM

可以分为四类，100 到 300 一类，400 一类，500 到 800 一类，900 最后一类。每一位上的情况都是类似的。

### 12.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;

	string int_to_roman(int num)
	{
		string res = "";
		vector<char> roman{'M', 'D', 'C', 'L', 'X', 'V', 'I'};
		vector<int> value{1000, 500, 100, 50, 10, 5, 1};
		for (int i = 0; i < 7; i += 2) {
			int x = num / value[i];
			if (x < 4) {
				for (int j = 0; j < x; j++) {
					res += roman[i];
				}
			} else if (x == 4) {
				res = res + roman[i] + roman[i - 1];
			} else if (x > 4 && x < 9) {
				res += roman[i - 1];
				for (int j = 6; j <= x; j++) {
					res = res + roman[i];
				}
			} else if (x == 9) {
				res = res + roman[i] + roman[i - 2];
			}

			num %= value[i];
		}
		return res;
	}
	//测试程序
	int main()
	{
		cout << int_to_roman(1437) << endl;
	}

## 13. Roman to Integer

### 13.1 Description

Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

	Input: "IX"
	Output: 9

Example 2:

	Input: "LVIII"
	Output: 58
	Explanation: L = 50, V= 5, III = 3.

Example 3:

	Input: "MCMXCIV"
	Output: 1994
	Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

### 13.2 Analysis

有几条须注意掌握：

	1、基本数字Ⅰ、X 、C 中的任何一个，自身连用构成数目，或者放在大数的右边连用构成数目，都不能超过三个；
		放在大数的左边只能用一个。
	2、不能把基本数字V 、L 、D 中的任何一个作为小数放在大数的左边采用相减的方法构成数目；放在大数的右边采
		用相加的方式构成数目，只能使用一个。
	3、V 和X 左边的小数字只能用Ⅰ。
	4、L 和C 左边的小数字只能用X。
	5、D 和M 左边的小数字只能用C。

用到 HashMap 数据结构，来将罗马数字的字母转化为对应的整数值，因为输入的一定是罗马数字，那么只要考虑两种情况即可：

	1.如果当前数字是最后一个数字，或者之后的数字比它小的话，则加上当前数字。
	2.其他情况则减去这个数字。

### 13.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	#include <unordered_map>
	using namespace std;

	int roman_to_int(string s)
	{
		int res = 0;
		unordered_map<char, int> m{{'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10},
			{'V', 5}, {'I', 1}};
		for (int i = 0; i < s.size(); i++) {
			int val = m[s[i]];
			if (i == s.size() - 1 || m[s[i + 1]] <= m[s[i]])
				res += val;
			else
				res -= val;
		}
		return res;
	}
	//测试程序
	int main()
	{
		cout << roman_to_int("MCDXXXVII") << endl;
	}

## 14. Longest Common Prefix

### 14.1 Description

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Example 1:

	Input: ["flower","flow","flight"]
	Output: "fl"

Example 2:

	Input: ["dog","racecar","car"]
	Output: ""
	Explanation: There is no common prefix among the input strings.

Note:

All given inputs are in lowercase letters a-z.

### 14.2 Analysis

定义两个变量i和j，其中i是遍历搜索字符串中的字符，j是遍历字符串集中的每个字符串。这里将单词上下排好，则相当于一个各行长度有可能不相等的二维数组，遍历顺序和一般的横向逐行遍历不同，而是采用纵向逐列遍历，在遍历的过程中，如果某一行没有了，说明其为最短的单词，因为共同前缀的长度不能长于最短单词，所以此时返回已经找出的共同前缀。每次取出第一个字符串的某一个位置的单词，然后遍历其他所有字符串的对应位置看是否相等，如果有不满足的直接返回 res，如果都相同，则将当前字符存入结果，继续检查下一个位置的字符。

### 14.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <string>
	using namespace std;

	string longest_common_prefix(vector<string> s)
	{
		if (s.empty())
			return "";
		string res = "";
		for (int i = 0; i < s[0].size(); i++) {
			char c = s[0][i];
			for (int j = 1; j < s.size(); j++) {
				if (i > s[j].size() || s[j][i] != c) {
					return res;
				}
			}
			res += c;
		}
		return res;
	}
	//测试代码
	int main()
	{
		vector<string> s{"flower", "flow", "flight"};
		cout << longest_common_prefix(s) << endl;
	}

## 15. 3Sum

### 15.1 Description

Given an array  S  of  n  integers, are there elements  a ,  b ,  c  in  S  such that  a  +  b  +  c  = 0? Find all unique triplets in the array which gives the sum of zero.

Note:Elements in a triplet ( a , b , c ) must be in non-descending order. (ie,  a  ≤  b  ≤  c )
The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},
    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)

### 15.2 Analysis

对原数组进行排序，然后开始遍历排序后的数组，这里注意不是遍历到最后一个停止，而是到倒数第三个就可以了。这里可以先做个剪枝优化，就是当遍历到正数的时候就 break，为啥呢，因为数组现在是有序的了，如果第一个要 fix 的数就是正数了，则后面的数字就都是正数，就永远不会出现和为0的情况了。然后还要加上重复就跳过的处理，处理方法是从第二个数开始，如果和前面的数字相等，就跳过，因为不想把相同的数字fix两次。对于遍历到的数，用0减去这个 fix 的数得到一个 target，然后只需要再之后找到两个数之和等于 target 即可。用两个指针分别指向 fix 数字之后开始的数组首尾两个数，如果两个数和正好为 target，则将这两个数和 fix 的数一起存入结果中。然后就是跳过重复数字的步骤了，两个指针都需要检测重复数字。如果两数之和小于 target，则将左边那个指针i右移一位，使得指向的数字增大一些。同理，如果两数之和大于 target，则将右边那个指针j左移一位，使得指向的数字减小一些。

### 15.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	vector<vector<int>> three_sum(vector<int> nums)
	{
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		if (nums.empty() || nums.back() < 0 || nums.front() > 0)
			return {};
		for (int i = 0; i < nums.size() - 2; i++) {
			if (nums[i] > 0)
				break;
			if (i > 0 && nums[i] == nums[i - 1])
				continue;
			int target = 0 - nums[i], j = i + 1, k = nums.size() - 1;
			while (j < k) {
				if (nums[j] + nums[k] == target) {
					res.pusk_back({nums[i], nums[j], nums[k]});
					while (j < k && nums[j + 1] == nums[j])
						j++;
					while (j < k && nums[k - 1] == nums[k])
						k--;
					j++;
					k--;
				} else if (nums[j] + nums[k] < target) {
					j++;
				} else {
					k--;
				}
			}
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> nums{-1, 0, 1, 2, -1, -4};
		vector<vector<int>> res = three_sum(nums);
		for (int i = 0; i < res.size(); i++) {
			for (int j = 0; j < res[i].size(); j++) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
	}
	//结果为
	-1 -1 2
	-1 0 1

## 16. 3Sum Closest

### 16.1 Description

Given an array nums of  n  integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

	Example:
	
	Given array nums = [-1, 2, 1, -4], and target = 1.
	
	The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

### 16.2 Analysis

保证当前三数和跟给定值之间的差的绝对值最小，需要定义一个变量 diff 用来记录差的绝对值，然后还是要先将数组排个序，然后开始遍历数组，思路跟那道三数之和很相似，都是先确定一个数，然后用两个指针 left 和 right 来滑动寻找另外两个数，每确定两个数，求出此三数之和，然后算和给定值的差的绝对值存在 newDiff 中，然后和 diff 比较并更新 diff 和结果 closest 即可。

### 16.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <algorithm>
	using namespace std;

	int three_sum_closest(vector<int> nums, int target)
	{
		sort(nums.begin(), nums.end());
		int closest = nums[0] + nums[1] + nums[2];
		int diff = abs(target - closest);
		for (int i = 0; i < nums.size() - 1; i++) {
			int left = i + 1, right = nums.size() - 1;
			while (left < right) {
				int sum = nums[i] + nums[left] + nums[right];
				int new_diff = abs(target - sum);
				if (new_diff < diff) {
					diff = new_diff;
					closest = sum;
				}

				if (sum < target)
					left++;
				else
					right--;
			}
		}
		return closest;
	}
	//测试程序
	int main()
	{
		vector<int> nums{-1, 1, 2, -4};
		cout << three_sum_closest(nums, 1) << endl;
	}

## 17. Letter Combination of a Phone Number

### 17.1 Description

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

	Example:
	
	Input: "23"
	Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

### 17.2 Analysis

这里可以用递归 Recursion 来解，需要建立一个字典，用来保存每个数字所代表的字符串，然后还需要一个变量 level，记录当前生成的字符串的字符个数。在递归函数中首先判断 level，如果跟 digits 中数字的个数相等了，将当前的组合加入结果 res 中，然后返回。我们通过 digits 中的数字到 dict 中取出字符串，然后遍历这个取出的字符串，将每个字符都加到当前的组合后面，并调用递归函数即可。

### 17.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <string>
	using namespace std;

	void letter_combination_dfs(string digits, vector<string> dict, int level, string out,
		vector<string> &res)
	{
		if (level == digits.size()) {
			res.push_back(out);
			return;
		}
		string str = dict[digits[level] - '0'];
		for (int i = 0; i < str.size(); i++) {
			letter_combination_dfs(digits, dict, level + 1, out + str[i], res);
		}
	}

	vector<string> letter_combination(string digits)
	{
		if (digits.empty())
			return {};
		vector<string> res;
		vector<string> dict{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
			//因为0, 1都是没有字母的
		letter_combination(digits, dict, 0, "", res);
		return res;
	}
	//测试程序
	int main()
	{
		string digits{"23"};
		vector<string> res = letter_combination(digits);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << " ";
		}
	}

## 18. 4Sum

### 18.1 Description

Given an array S of n integers, are there elements a , b , c , and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

Elements in a quadruplet(a, b, c, d)must be in non-descending order.(ie, a ≤ b ≤ c ≤ d )

The solution set must not contain duplicate quadruplets.

	For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
	A solution set is:
	(-1,  0, 0, 1)
	(-2, -1, 1, 2)
	(-2,  0, 0, 2)

### 18.2 Analysis

为了避免重复项，我们使用了 STL 中的 TreeSet，其特点是不能有重复，如果新加入的数在 TreeSet 中原本就存在的话，插入操作就会失败，这样能很好的避免的重复项的存在。此题的 O(n^3) 解法的思路跟 3Sum 基本没啥区别。

### 18.3 Code

**1.Solution 1**

	#include <iostream>
	#include <set>
	#include <vector>
	#include <algorithm>
	using namespace std;

	vector<vector<int>> four_sum(vector<int> nums, int target)
	{
		set<vector<int>> res;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 3; i++) {
			for (int j = i + 1; j < nums.size() - 2; j++) {
				if (j > i + 1 && nums[j] == nums[j - 1])
					continue;

				int left = j + 1, right = nums.size() - 1;
				while (left < right) {
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum == target) {
						vector<int> out{nums[i], nums[j], nums[left], nums[right]};
						res.insert(out);
						left++;
						right--;
					} else if (sum < target) {
						left++;
					} else {
						right--;
					}
				}
			}
		}
		return vector<vector<int>>(res.begin(), res.end());
	}
	//测试程序
	int main()
	{
		vector<int> nums{1, 0, -1, 0, -2, 2};
		vector<vector<int>> res = four_sum(nums, 0);
	
		for (int i = 0; i < res.size(); i++) {
			for (int j = 0; j < res[i].size(); j++) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
	}

## 19. Remove Nth Node From End of List

### 19.1 Description

Given a linked list, remove the n-th node from the end of list and return its head.

	For example,
	Given linked list: **1- >2->3->4->5**, and **_n_ = 2**.	
	After removing the second node from the end, the linked list becomes **1- >2->3->5**.

### 19.2 Analysis

首先要考虑的是，如何找到倒数第N个节点，由于只允许一次遍历，所以不能用一次完整的遍历来统计链表中元素的个数，而是遍历到对应位置就应该移除了。那么就需要用两个指针来帮助解题，pre 和 cur 指针。首先 cur 指针先向前走N步，如果此时 cur 指向空，说明N为链表的长度，则需要移除的为首元素，那么此时返回 head->next 即可，如果 cur 存在，再继续往下走，此时pre指针也跟着走，直到 cur 为最后一个元素时停止，此时 pre 指向要移除元素的前一个元素，再修改指针跳过需要移除的元素即可。

### 19.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	struct list_node {
		int val
		list_node *next;
		list_node(int v) :
			val(v),
			next(nullptr)
		{}
	};

	list_node *remove_nth_from_end(list_node *head, int n)
	{
		if (!head->next)
			return nullptr;
		list_node *pre = head, *cur = head;
		for (int i = 0; i < n; i++)
			cur = cur->next;
		if (!cur->next)
			return head->next;

		while (cur->next) {
			cur = cur->next;
			pre = pre->next;
		}
		pre->next = pre->next->next;
		return head;
	}
	//测试程序
	int main()
	{
		list_node *head = new list_node(-1);
		list_node *cur = head;
		cur->next = new list_node(1);
		cur = cur->next;
		cur->next = new list_node(2);
		cur = cur->next;
		cur->next = new list_node(3);
		cur = cur->next;
		cur->next = new list_node(4);
		cur = cur->next;
		cur->next = new list_node(5);
		cur = cur->next;
		list_node *res = remove_nth_from_end(head, 2);
	
		cur = res->next;
		while (cur) {
			cout << cur->val << " ";
			cur = cur->next;
		}
	}

## 20. Valid Parentheses

### 20.1 Description

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid. An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

	Input: "()[]{}"
	Output: true

Example 2:

	Input: "([)]"
	Output: false

Example 3:

	Input: "{[]}"
	Output: true

### 20.2 Analysis

验证输入的字符串是否为括号字符串，包括大括号，中括号和小括号。这里需要用一个栈，开始遍历输入字符串，如果当前字符为左半边括号时，则将其压入栈中，如果遇到右半边括号时，若此时栈为空，则直接返回 false，如不为空，则取出栈顶元素，若为对应的左半边括号，则继续循环，反之返回 false。

### 20.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	#include <stack>
	using namespace std;

	bool is_valid(string s)
	{
		stack<char> parentheses;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{')
				parentheses.push(s[i]);
			else {
				if (parentheses.empty())
					return false;
				if (s[i] == ')' && parentheses.top() != '(')
					return false;
				if (s[i] == ']' && parentheses.top() != '[')
					return false;
				if (s[i] == '}' && parentheses.top() != '{')
					return false;
				parentheses.pop();
			}
		}
		return parentheses.empty();
	}
	//测试程序
	int main()
	{
		cout << boolalpha << is_valid("{[]}");
	}

## 21. Merge Two Sorted Lists

### 21.1 Description

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

	Input: 1->2->4, 1->3->4
	Output: 1->1->2->3->4->4

### 21.2 Analysis

具体思想就是新建一个链表，然后比较两个链表中的元素值，把较小的那个链到新链表中，由于两个输入链表的长度可能不同，所以最终会有一个链表先完成插入所有元素，则直接另一个未完成的链表直接链入新链表的末尾。

### 21.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	struct list_node {
		int val;
		list_node *next;
		list_node(int v) :
			val(v),
			next(nullptr)
		{}
	};

	list_node *merge_two_lists(list_node *l1, list_node *l2)
	{
		list_node *dummy = new list_node(-1), *cur = dummy;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				cur->next = l1;
				l1 = l1->next;
			} else {
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		cur->next = l1 ? l1 : l2;
		return dummy->next;
	}
	//测试程序
	int main()
	{
		list_node *l1 = new list_node(1), *cur = l1;
		cur->next = new list_node(2);
		cur = cur->next;
		cur->next = new list_node(4);
		cur = cur->next;
	
		list_node *l2 = new list_node(1);
		cur = l2;
		cur->next = new list_node(3);
		cur = cur->next;
		cur->next = new list_node(4);
		cur = cur->next;
	
		list_node *res = merge_two_lists(l1, l2);
		while (res) {
			cout << res->val << " ";
			res = res->next;
		}
	}

## 22. Generate Parentheses

### 22.1 Description

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given  n  = 3, a solution set is:

	[
	  "((()))",
	  "(()())",
	  "(())()",
	  "()(())",
	  "()()()"
	]

### 22.2 Analysis

给定一个数字n，让生成共有n个括号的所有正确的形式，对于这种列出所有结果的题首先还是考虑用递归 Recursion 来解，由于字符串只有左括号和右括号两种字符，而且最终结果必定是左括号3个，右括号3个，所以这里定义两个变量 left 和 right 分别表示剩余左右括号的个数，如果在某次递归时，左括号的个数大于右括号的个数，说明此时生成的字符串中右括号的个数大于左括号的个数，即会出现 ')(' 这样的非法串，所以这种情况直接返回，不继续处理。如果 left 和 right 都为0，则说明此时生成的字符串已有3个左括号和3个右括号，且字符串合法，则存入结果中后返回。如果以上两种情况都不满足，若此时 left 大于0，则调用递归函数，注意参数的更新，若 right 大于0，则调用递归函数，同样要更新参数。

### 22.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;

	void generate_parentheses_dfs(int left, int right, string out, vector<string> &res)
	{
		if (left > right)
			return;
		if (left == 0 && right == 0)
			res.push_back(out);
		else {
			if (left > 0)
				generate_parentheses_dfs(left - 1, right, out + '(', res);
			if (right > 0)
				generate_parentheses_dfs(left, right - 1, out + ')', res);
		}
	}
	
	vector<string> generate_parentheses(int n)
	{
		vector<string> res;
		generate_parentheses(n, n, "", res);
		return res;
	}
	//测试程序
	int main()
	{
		vector<string> res;
		res = generate_parentheses(3);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << endl;
		}
		return 0;
	}

## 23. Merge K Sorted Lists

### 23.1 Description

### 23.2 Analysis

### 23.3 Code

**1.Solution 1**

## 24. Swap Nodes in Pairs

### 24.1 Description

Given a linked list, swap every two adjacent nodes and return its head. You may not modify the values in the list's nodes, only nodes itself may be changed.

Example:

	Given 1->2->3->4, you should return the list as 2->1->4->3.

### 24.2 Analysis

基本的链表操作题，我们可以分别用递归和迭代来实现。对于迭代实现，还是需要建立 dummy 节点，注意在连接节点的时候，最好画个图，以免把自己搞晕了。

### 24.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	struct list_node {
		int val;
		list_node *next;
		list_node(int v) :
			val(v),
			next(nullptr)
		{}
	};

	list_node *swap_pairs(list_node *head)
	{
		list_node *dummy = new list_node(-1), *prev = dummy;
		dummy->next = head;
		while (prev->next && prev->next->next) {
			list_node *t = prev->next->next;
			prev->next->next = t->next;
			t->next = prev->next;
			prev->next = t;
			prev = t->next;
		}
		return dummy->next;
	}
	//测试程序
	int main()
	{
		list_node *head = new list_node(1);
		list_node *cur = head;
		cur->next = new list_node(2);
		cur = cur->next;
		cur->next = new list_node(3);
		cur = cur->next;
		cur->next = new list_node(4);
		cur = cur->next;
		cur->next = new list_node(5);
		list_node *res = swap_pairs(head);
		while (res) {
			cout << res->val << " ";
			res = res->next;
		}
	}

## 25. Reverse Nodes in k-Group

### 25.1 Description

### 25.2 Analysis

### 25.3 Code

**1.Solution 1**

## 26. Remove Duplicates from Sorted Array

### 26.1 Description

Given a sorted array  nums , remove the duplicates in-place such that each element appear only  once  and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Example:

	Given _nums_ = [0,0,1,1,1,2,2,3,3,4],
	Your function should return length = 5, with the first five elements of _nums_ being 
	modified to 0, 1, 2, 3, and 4 respectively.It doesn't matter what values are set beyond
	the returned length.

### 26.2 Analysis

这道题的解题思路是使用快慢指针来记录遍历的坐标，最开始时两个指针都指向第一个数字，如果两个指针指的数字相同，则快指针向前走一步，如果不同，则两个指针都向前走一步，这样当快指针走完整个数组后，慢指针当前的坐标加1就是数组中不同数字的个数。

### 26.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	int remove_duplicates(vector<int> &nums)
	{
		int prev = 0, cur = 0, n = nums.size();
		while (cur < n) {
			if (nums[prev] == nums[cur])
				cur++;
			else
				nums[++prev] = nums[cur++];
		}
		return nums.empty() ? 0 : (prev + 1);
	}
	//测试程序
	int main()
	{
		vector<int> nums{0,0,1,1,1,2,2,3,3,4};
		cout << remove_duplicates(nums);
	}

## 27. Remove Element

### 27.1 Description

Given an array  nums  and a value  val , remove all instances of that value in-place and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example:

	Given _nums_ = [0,1,2,2,3,0,4,2], _val_ = 2,
	Your function should return length = 5, with the first five elements of _nums_ containing
	0, 1, 3, 0, and 4.
	Note that the order of those five elements can be arbitrary.
	It doesn't matter what values are set beyond the returned length.

### 27.2 Analysis

让我们移除一个数组中和给定值相同的数字，并返回新的数组的长度。是一道比较容易的题,只需要一个变量用来计数，然后遍历原数组，如果当前的值和给定值不同，就把当前值覆盖计数变量的位置，并将计数变量加1。

### 27.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	int remove_element(vector<int> &nums, int val)
	{
		int res = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != val)
				nums[res++] = nums[i];
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> nums{0,1,2,2,3,0,4,2};
		cout << remove_element(nums, 2) << endl;
	}

## 28. Implement strStr()

### 28.1 Description

Implement strStr(). Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

	Input: haystack = "hello", needle = "ll"
	Output: 2

Example 2:

	Input: haystack = "aaaaa", needle = "bba"
	Output: -1

### 28.2 Analysis

让我们在一个字符串中找另一个字符串第一次出现的位置，那首先要做一些判断，如果子字符串为空，则返回0，如果子字符串长度大于母字符串长度，则返回 -1。然后开始遍历母字符串，这里并不需要遍历整个母字符串，而是遍历到剩下的长度和子字符串相等的位置即可，这样可以提高运算效率。然后对于每一个字符，都遍历一遍子字符串，一个一个字符的对应比较，如果对应位置有不等的，则跳出循环，如果一直都没有跳出循环，则说明子字符串出现了，则返回起始位置即可。

### 28.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	using namespace std;

	int str_str(string haystack, string needle)
	{
		if (needle.empty())
			return 0;
		int m = haystack.size(), n = needle.size();
		if (m < n)
			return -1;
		for (int i = 0; i < m - n; i++) {
			int j = 0;
			for (int j = 0; j < n; j++) {
				if (haystack[i + j] != needle[j])
					break;
			}
			if (j == n)
				return i;
		}
		return -1;
	}
	//测试程序
	int main()
	{
		string haystack{"hello"};
		string needle{"ll"};
		cout << str_str(haystack, needle) << endl;
	}

## 29. Divide Two Integers

### 29.1 Description

Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.Return the quotient after dividing dividend by divisor.The integer division should truncate toward zero.

Example 1:

	Input: dividend = 10, divisor = 3
	Output: 3

Example 2:

	Input: dividend = 7, divisor = -3
	Output: -2

### 29.2 Analysis

这道题让我们求两数相除，而且规定不能用乘法，除法和取余操作，那么这里可以用另一神器位操作 Bit Manipulation，思路是，如果被除数大于或等于除数，则进行如下循环，定义变量t等于除数，定义计数p，当t的两倍小于等于被除数时，进行如下循环，t扩大一倍，p扩大一倍，然后更新 res 和m。这道题的 OJ 给的一些 test case 非常的讨厌，因为输入的都是 int 型，比如被除数是 -2147483648，在 int 范围内，当除数是  -1 时，结果就超出了 int 范围，需要返回 INT_MAX，所以对于这种情况就在开始用 if 判定，将其和除数为0的情况放一起判定，返回 INT_MAX。然后还要根据被除数和除数的正负来确定返回值的正负，这里采用长整型 long 来完成所有的计算，最后返回值乘以符号即可。

### 29.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	int divide(int dividend, int divisor)
	{
		if (dividend == INT_MIN && divisor == -1)
			return INT_MAX;
		long m = labs(dividend), n = labs(divisor), res = 0;
		int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
		if (n == 1)
			return (sign == 1) ? m : -m;
		while (m >= n) {
			long t = n, p = 1;
			while (m >= (t << 1)) {
				t <<= 1;
				p <<= 1;
			}
			res += p;
			m -= t;
		}
		return (sign == 1) ? res : -res;
	}
	//测试程序
	int main()
	{
		cout << divide(10, 3) << endl;
		cout << divide(7, -3) << endl;
	}

## 30. Substring with Concatenation of All Words

### 30.1 Description

### 30.2 Analysis

### 30.3 Code

**1.Solution 1**

## 31. Next Permutation

### 31.1 Description

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

	1,2,3 → 1,3,2
	3,2,1 → 1,2,3
	1,1,5 → 1,5,1

### 31.2 Analysis

由题目中给的例子可以看出来，如果给定数组是降序，则说明是全排列的最后一种情况，则下一个排列就是最初始情况。

再来看下面一个例子，有如下的一个数组

	1　　2　　7　　4　　3　　1

下一个排列为：

	1　　3　　1　　2　　4　　7

那么是如何得到的呢，我们通过观察原数组可以发现，如果从末尾往前看，数字逐渐变大，到了2时才减小的，然后再从后往前找第一个比2大的数字，是3，那么我们交换2和3，再把此时3后面的所有数字转置一下即可，步骤如下：

	1　　2　　7　　4　　3　　1
	1　　2　　7　　4　　3　　1
	1　　3　　7　　4　　2　　1
	1　　3　　1　　2　　4　　7

### 31.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	void next_permutation(vector<int> &num)
	{
		int i, j, n = num.size();
		for (i = n - 2; i >= 0; i--) {
			if (num[i + 1] > num[i]) {
				for (j = n - 1; j > i; j--) {
					if (num[j] > num[i])
						break;
				}
				swap(num[i], num[j]);
				reverse(num.begin() + i + 1, num.end());
				return;
			}
		}
		reverse(num.begin(), num.end());
	}
	//测试程序
	int main()
	{
		vector<int> num{1, 2, 7, 4, 3, 1};
		next_permutation(num);
		for (int i = 0; i < num.size(); i++) {
			cout << num[i] << " ";
		}
	}

## 32. Longest Valid Parentheses

### 32.1 Description

### 32.2 Analysis

### 32.3 Code

**1.Solution 1**

## 33. Search in Rotated Sorted Array

### 33.1 Description

### 33.2 Analysis

### 33.3 Code

**1.Solution 1**

## 34. Find First and Last Position of Element in Sorted Array

### 34.1 Description

Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value. Your algorithm's runtime complexity must be in the order of  O (log  n).

If the target is not found in the array, return [-1, -1].

Example 1:

	Input: nums = [5,7,7,8,8,10], target = 8
	Output: [3,4]

Example 2:

	Input: nums = [5,7,7,8,8,10], target = 6
	Output: [-1,-1]

### 34.2 Analysis

这道题让我们在一个有序整数数组中寻找相同目标值的起始和结束位置，而且限定了时间复杂度为 O(logn)，这是典型的二分查找法的时间复杂度，所以这里也需要用此方法，思路是首先对原数组使用二分查找法，找出其中一个目标值的位置，然后向两边搜索找出起始和结束的位置。

### 34.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	int search(vector<int> nums, int left, int right, int target)
	{
		if (left > right)
			return -1;
		int mid = left + (right - left) / 2;
		if (nums[mid] == target)
			return mid;
		else if (nums[mid] < target)
			return search(nums, mid + 1, right, target);
		else
			return search(nums, left, mid - 1, target);
	}

	vector<int> search_range(vector<int> nums, int target)
	{
		int idx = search(nums, 0, nums.size() - 1, target);
		if (idx == -1)
			return {-1, -1};
		int left = idx, right = idx;
		while (left > 0 && (nums[left - 1] == nums[idx]))
			left--;
		while ((right < nums.size() - 1) && (nums[right + 1] == nums[idx]))
			right++;
		return {left, right};
	}
	//测试程序
	int main()
	{
		vector<int> num{ 5,7,7,8,8,10 };
		vector<int> res;
		res = search_range(num, 8);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i] << " ";
		}
	}

## 35. Search Insert Position

### 35.1 Description

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order. You may assume no duplicates in the array.

Example 1:

	Input: [1,3,5,6], 5
	Output: 2

Example 2:

	Input: [1,3,5,6], 2
	Output: 1

Example 3:

	Input: [1,3,5,6], 7
	Output: 4

Example 4:

	Input: [1,3,5,6], 0
	Output: 0

### 35.2 Analysis

遍历一遍原数组，若当前数字大于或等于目标值，则返回当前坐标，如果遍历结束了，说明目标值比数组中任何一个数都要大，则返回数组长度n即可。

### 35.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	int search_insert(vector<int> nums, int target)
	{
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] >= target) {
				return i;
			}
		}
		return nums.size();
	}

## 36. Valid Sudoku

### 36.1 Description

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

	Each row must contain the digits 1-9without repetition.
	Each column must contain the digits 1-9 without repetition.
	Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

![](images/valid_sudoku.png)

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Example 1:

	Input:
	[
	  ["5","3",".",".","7",".",".",".","."],
	  ["6",".",".","1","9","5",".",".","."],
	  [".","9","8",".",".",".",".","6","."],
	  ["8",".",".",".","6",".",".",".","3"],
	  ["4",".",".","8",".","3",".",".","1"],
	  ["7",".",".",".","2",".",".",".","6"],
	  [".","6",".",".",".",".","2","8","."],
	  [".",".",".","4","1","9",".",".","5"],
	  [".",".",".",".","8",".",".","7","9"]
	]
	Output: true

Example 2:

	Input:
	[
	  ["8","3",".",".","7",".",".",".","."],
	  ["6",".",".","1","9","5",".",".","."],
	  [".","9","8",".",".",".",".","6","."],
	  ["8",".",".",".","6",".",".",".","3"],
	  ["4",".",".","8",".","3",".",".","1"],
	  ["7",".",".",".","2",".",".",".","6"],
	  [".","6",".",".",".",".","2","8","."],
	  [".",".",".","4","1","9",".",".","5"],
	  [".",".",".",".","8",".",".","7","9"]
	]
	Output: false
	Explanation: Same as Example 1, except with the 5 in the top left corner being 
	    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Note:

	A Sudoku board (partially filled) could be valid but is not necessarily solvable.
	Only the filled cells need to be validated according to the mentioned rules.
	The given board contain only digits 1-9and the character '.'.
	The given board size is always 9x9.

### 36.2 Analysis

这道题给了一个残缺的二维数组，让我们判断当前的这个数独数组是否合法，即要满足上述的条件。判断标准是看各行各列是否有重复数字，以及每个小的 3x3 的小方阵里面是否有重复数字，如果都无重复，则当前矩阵是数独矩阵，但不代表待数独矩阵有解，只是单纯的判断当前未填完的矩阵是否是数独矩阵。那么根据数独矩阵的定义，在遍历每个数字的时候，就看看包含当前位置的行和列以及 3x3 小方阵中是否已经出现该数字，这里需要三个 boolean 型矩阵，大小跟原数组相同，分别记录各行，各列，各小方阵是否出现某个数字，其中行和列标志下标很好对应，就是小方阵的下标需要稍稍转换一下。

### 36.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	bool is_valid_sudoku(vector<vector<char>> &board)
	{
		vector<vector<bool>> row_flag(9, vector<bool>(9));
		vector<vector<bool>> col_flag(9, vector<bool>(9));
		vector<vector<bool>> cell_flag(9, vector<bool>(9));

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == '.')
					continue;
				int c = board[i][j] - '1';
				if (row_flag[i][c] || col_flag[c][j] || cell_flag[3*(i/3)+j/3][c])
					return false;
				row_flag[i][c] = true;
				col_flag[c][j] = true;
				cell_flag[3*(i/3)+j/3][c] = true;
			}
		}
		return true;
	}
	//测试程序
	int main()
	{
		vector<vector<char>> board{
		  {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
		};
		// char字符应该以单引号''包含,双引号""表示字符串
		cout << boolalpha << is_valid_sudoku(board) << endl;
	}

## 37. Sudoku Solver

### 37.1 Description

### 37.2 Analysis

### 37.3 Code

**1.Solution 1**

## 38. Count and Say

### 38.1 Description

The count-and-say sequence is the sequence of integers with the first five terms as following:

	1.     1
	2.     11
	3.     21
	4.     1211
	5.     111221

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer  n  where 1 ≤  n  ≤ 30, generate the  n th term of the count-and-say sequence.

### 38.2 Analysis

其实就是第i+1个字符串是第i个字符串的读法，第一字符串为 “1”。比如第四个字符串是1211，它的读法是 1个1、1个2,2个1，因此第五个字符串是111221。第五个字符串的读法是：3个1、2个2、1个1，因此第六个字符串是312211 

### 38.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	using namespace std;

	string count_and_say(int n)
	{
		if (n <= 0)
			return "";
		string res = "1";
		while (--n) {
			string cur = "";
			for (int i = 0; i < res.size(); i++) {
				int cnt = 1;
				while ((i + 1 < res.size()) && res[i + 1] == res[i]) {
					++cnt;
					++i;
				}
				cur += to_string(cnt) + res[i];
			}
			cout << cur << endl;
			res = cur;
		}
		return res;
	}
	//测试程序
	int main()
	{
		string res = count_and_say(12);
	}

## 39. Combination Sum

### 39.1 Description

Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.The same repeated number may be chosen from candidates unlimited number of times.

Note:

All numbers (including target) will be positive integers.The solution set must not contain duplicate combinations.

Example 1:

	Input: candidates = [2,3,6,7], target = 7,
	A solution set is:
	[
	  [7],
	  [2,2,3]
	]

Example 2:

	Input: candidates = [2,3,5], target = 8,
	A solution set is:
	[
	  [2,2,2,2],
	  [2,3,3],
	  [3,5]
	]

### 39.2 Analysis

像这种结果要求返回所有符合要求解的题十有八九都是要利用到递归，而且解题的思路都大同小异，相类似的题目有 Path Sum II，Subsets II，Permutations，Permutations II，Combinations 等等，如果仔细研究这些题目发现都是一个套路，都是需要另写一个递归函数，这里我们新加入三个变量，start 记录当前的递归到的下标，out 为一个解，res 保存所有已经得到的解，每次调用新的递归函数时，此时的 target 要减去当前数组的的数。

### 39.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	void combination_sum_dfs(vector<vector<int>> candidates, int target, int start,
		vector<int> &out, vector<vector<int>> &res)
	{
		if (target < 0)
			return;
		if (target == 0) {
			res.push_back(out);
			return;
		}
		for (int i = start; i < candidates.size(); i++) {
			out.push_back(candidates[i]);
			combination_sum_dfs(candidates, target - candidates[i], i, out, res);
			out.pop_back();
		}
	}

	vector<vector<int>> combination_sum(vector<int> &candidates, int target)
	{
		vector<vector<int>> res;
		vector<int> out;
		combination_sum_dfs(candidates, target, 0, out, res);
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> candidates{ 2,3,6,7 };
		vector<vector<int>> res = combination_sum(candidates, 7);
		for (int i = 0; i < res.size(); i++) {
			for (int j = 0; j < res[i].size(); j++) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
	}

## 40. Combination Sum II

### 40.1 Description

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.Each number in candidates may only be used once in the combination.

Note:All numbers (including target) will be positive integers. The solution set must not contain duplicate combinations.

Example 1:

	Input: candidates = [10,1,2,7,6,1,5], target = 8,
	A solution set is:
	[
	  [1, 7],
	  [1, 2, 5],
	  [2, 6],
	  [1, 1, 6]
	]

Example 2:

	Input: candidates = [2,5,2,1,2], target = 5,
	A solution set is:
	[
	  [1,2,2],
	  [5]
	]

### 40.2 Analysis

这道题跟之前那道Combination Sum本质没有区别，只需要改动一点点即可，之前那道题给定数组中的数字可以重复使用，而这道题不能重复使用，只需要在之前的基础上修改两个地方即可，首先在递归的 for 循环里加上 if (i > start && num[i] == num[i - 1]) continue; 这样可以防止 res 中出现重复项，然后就在递归调用 helper 里面的参数换成 i+1，这样就不会重复使用数组中的数字了。

### 40.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	void helper(vector<int> &num, int target, int start, vector<int> out,
		vector<vector<int>> &res)
	{
		if (target < 0)
			return;
		if (target == 0) {
			res.push_back(out);
			return;
		}

		for (int i = start; i < num.size(); i++) {
			if (i > start && num[i] == num[i - 1])
				continue;
			out.push_back(num[i]);
			helper(num, target - num[i], i + 1, out, res);
			out.pop_back();
		}
	}

	vector<vector<int>> combination_sum2(vector<int> &num, int target)
	{
		vector<vector<int>> res;
		vector<int> out;
		sort(num.begin(), num.end());
		helper(num, target, 0, out, res);
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> candidates{ 2,3,6,7 };
		vector<vector<int>> res = combination_sum_2(candidates, 7);
		for (int i = 0; i < res.size(); i++) {
			for (int j = 0; j < res[i].size(); j++) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
	}

## 41. First Missing Positive

### 41.1 Description

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

	Input: [1,2,0]
	Output: 3

Example 2:

	Input: [3,4,-1,1]
	Output: 2

Example 3:

	Input: [7,8,9,11,12]
	Output: 1

Note:

Your algorithm should run in  O ( n ) time and uses constant extra space.--->暂时不满足.

### 41.2 Analysis

使用HashSet来解，这个思路很简单，把所有的数都存入 HashSet 中，然后循环从1开始递增找数字，哪个数字找不到就返回哪个数字，如果一直找到了最大的数字（这里是 nums 数组的长度），则加1后返回结果res。

	限制空间复杂度，暂时不做。

### 41.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <unordered_set>
	using namespace std;

	int first_missing_positive(vector<int> &nums)
	{
		unordered_map<int> st(nums.begin(), nums.end());
		int res = 1, n = nums.size();
		while (res <= n) {
			if (!st.count(res))
				return res;
			res++;
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> nums{ 7,8,9,11,12 };
		cout << first_miss_positive(nums) << endl;
	}

## 42. Trapping Rain Water

### 42.1 Description

### 42.2 Analysis

### 42.3 Code

**1.Solution 1**

## 43. Multiply Strings

### 43.1 Description

Given two non-negative integers num1 and num2represented as strings, return the product of num1 and num2, also represented as a string.

Example 1:

	Input: num1 = "2", num2 = "3"
	Output: "6"

Example 2:

	Input: num1 = "123", num2 = "456"
	Output: "56088"

Note:

	1.The length of both num1 and num2 is < 110.
	2.Both num1 and num2 contain only digits 0-9.
	3.Both num1 and num2 do not contain any leading zero, except the number 0 itself.
	4.You must not use any built-in BigInteger libraryor convert the inputs to integer 
		directly.

### 43.2 Analysis

根据小学的算术知识，不难写出计算过程如下：

	    8 9  <- num2
	    7 6  <- num1
	-------
	    5 4
	  4 8
	  6 3
	5 6
	-------
	6 7 6 4

不难发现，两数相乘得到的乘积的长度其实其实不会超过两个数字的长度之和，若 num1 长度为m，num2 长度为n，则 num1 x num2 的长度不会超过 m+n，还有就是要明白乘的时候为什么要错位，比如6乘8得到的 48 为啥要跟6乘9得到的 54 错位相加，因为8是十位上的数字，其本身相当于80，所以错开的一位实际上末尾需要补的0。还有一点需要观察出来的就是，num1 和 num2 中任意位置的两个数字相乘，得到的两位数在最终结果中的位置是确定的，比如 num1 中位置为i的数字乘以 num2 中位置为j的数字，那么得到的两位数字的位置为 i+j 和 i+j+1，明白了这些后，就可以进行错位相加了，累加出最终的结果。

由于要从个位上开始相乘，所以从 num1 和 num2 字符串的尾部开始往前遍历，分别提取出对应位置上的字符，将其转为整型后相乘。然后确定相乘后的两位数所在的位置 p1 和 p2，由于 p2 相较于 p1 是低位，所以将得到的两位数 mul 先加到 p2 位置上去，这样可能会导致 p2 位上的数字大于9，所以将十位上的数字要加到高位 p1 上去，只将余数留在 p2 位置，这样每个位上的数字都变成一位。然后要做的是从高位开始，将数字存入结果 res 中，记住 leading zeros 要跳过，最后处理下 corner case，即若结果 res 为空，则返回 "0"，否则返回结果 res

### 43.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;

	string multiply(string num1, string num2)
	{
		string res = "";
		int m = num1.size(), n = num2.size();
		vector<int> vals(m + n);
		for (int i = m - 1; i >= 0; i--) {
			for (int j = n - 1; j >= 0; j--) {
				int mul = (num1[i] - '0') * (num2[j] - '0');
				int p1 = i + j, p2 = i + j + 1, sum = mul + vals[p2];
				vals[p1] += sum / 10;
				vals[p2] = sum % 10;
			}
		}
		for (int val : vals) {
			if (!res.empty() || (val != 0))
				res.push_back(val + '0');
		}
		return (res.empty() ? "0" : res);
	}
	//测试程序
	int main()
	{
		cout << multiply("123", "456") << endl;
	}

## 44. Wildcard Matching

### 44.1 Description

### 44.2 Analysis

### 44.3 Code

**1.Solution 1**

## 45. Jump Game II

### 45.1 Description

### 45.2 Analysis

### 45.3 Code

**1.Solution 1**

## 46. Permutations

### 46.1 Description

Given a collection of distinct integers, return all possible permutations.

Example:

	Input: [1,2,3]
	Output:
	[
	  [1,2,3],
	  [1,3,2],
	  [2,1,3],
	  [2,3,1],
	  [3,1,2],
	  [3,2,1]
	]

### 46.2 Analysis

此题是求全排列问题，还是用递归 DFS 来求解。这里需要用到一个 visited 数组来标记某个数字是否访问过，然后在 DFS 递归函数从的循环应从头开始，而不是从 level 开始，这是和 Combinations 不同的地方，其余思路大体相同。这里再说下 level 吧，其本质是记录当前已经拼出的个数，一旦其达到了 nums 数组的长度，说明此时已经是一个全排列了，因为再加数字的话，就会超出。还有就是，为啥这里的 level 要从0开始遍历，因为这是求全排列，每个位置都可能放任意一个数字，这样会有个问题，数字有可能被重复使用，由于全排列是不能重复使用数字的，所以需要用一个 visited 数组来标记某个数字是否使用过。

### 46.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	void permute(vector<int> &num, int level, vector<int> &visited, vector<int> &out,
		vector<vector<int>> &res)
	{
		if (level == num.size()) {
			res.push_back(out);
			return;
		}
		for (int i = 0; i < num.size(); i++) {
			if (visited[i] == 1)
				continue;
			visited[i] = 1;
			out.push_back(num[i]);
			permute(num, level + 1, visited, out, res);
			out.pop_back();
			visited[i] = 0;
		}
	}

	vector<vector<int>> permute(vector<int> &num)
	{
		vector<vector<int>> res;
		vector<int> out, visited(num.size(), 0);
		permute_dfs(num, 0, visited, out, res);
		return res;
	}

	//测试程序
	int main()
	{
		vector<int> num{1, 2, 3};
		vector<vector<int>> res = permute(num);
		for (vector<int> vec1 : res) {
			for (int val : vec1) {
				cout << val << " ";
			}
			cout << endl;
		}
	}

## 47. Permutations II

### 47.1 Description

### 47.2 Analysis

### 47.3 Code

**1.Solution 1**

## 48. Rotate Image

### 48.1 Description

### 48.2 Analysis

### 48.3 Code

**1.Solution 1**

## 49. Group Anagrams

### 49.1 Description

Given an array of strings, group anagrams together.

Example:

	Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
	Output:
	[
	  ["ate","eat","tea"],
	  ["nat","tan"],
	  ["bat"]
	]

Note:

	All inputs will be in lowercase.
	The order of your output does not matter.

### 49.2 Analysis

这道题让我们群组给定字符串集中所有的错位词，所谓的错位词就是两个字符串中字母出现的次数都一样，只是位置不同，比如 abc，bac, cba 等它们就互为错位词，那么如何判断两者是否是错位词呢，可以发现如果把错位词的字符顺序重新排列，那么会得到相同的结果，所以重新排序是判断是否互为错位词的方法，由于错位词重新排序后都会得到相同的字符串，以此作为 key，将所有错位词都保存到字符串数组中，建立 key 和字符串数组之间的映射，最后再存入结果 res 中即可。

### 49.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <string>
	#include <unordered_map>
	using namespace std;

	vector<vector<string>> group_anagrams(vector<string> &strs)
	{
		vector<vector<string>> res;
		unordered_map<string, vector<string>> m;
		for (string str : strs) {
			string t = str;
			sort(t.begin(), t.end());
			m[t].push_back(str);
		}
		for (auto a : m) {
			res.push_back(a.second);
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<string> strs{ "eat", "tea", "tan", "ate", "nat", "bat" };
		vector<vector<string>> res = group_anagrams(strs);
		for (vector<string> vec_str : res) {
			for (string str : vec_str) {
				cout << str << " ";
			}
			cout << endl;
		}
	}
	
## 50. Pow(x, n)

### 50.1 Description

### 50.2 Analysis

### 50.3 Code

**1.Solution 1**

## 51. N-Queens

### 51.1 Description

### 51.2 Analysis

### 51.3 Code

**1.Solution 1**

## 52. N-Queens II

### 52.1 Description

### 52.2 Analysis

### 52.3 Code

**1.Solution 1**

## 53. Maximum Subarray

### 53.1 Description

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

	Input: [-2,1,-3,4,-1,2,1,-5,4],
	Output: 6
	Explanation: [4,-1,2,1] has the largest sum = 6.

### 53.2 Analysis

求最大子数组之和.定义两个变量 res 和 curSum，其中 res 保存最终要返回的结果，即最大的子数组之和，curSum 初始值为0，每遍历一个数字 num，比较 curSum + num 和 num 中的较大值存入 curSum，然后再把 res 和 curSum 中的较大值存入 res，以此类推直到遍历完整个数组，可得到最大子数组的值存在res中。

### 53.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	int max_sub_array(vector<int> &nums)
	{
		int res = INT_MIN, cur_sum = 0;
		for (int num : nums) {
			cur_sum = max(cur_sum + num, num);
			res = max(cur_sum, res);
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<int> nums{ -2,1,-3,4,-1,2,1,-5,4 };
		cout << max_sub_array(nums) << endl;
	}

## 54. Spiral Matrix

### 54.1 Description

Given a matrix of  m  x  n  elements ( m  rows,  n columns), return all elements of the matrix in spiral order.

Example 1:

	Input:
	[
	 [ 1, 2, 3 ],
	 [ 4, 5, 6 ],
	 [ 7, 8, 9 ]
	]
	Output: [1,2,3,6,9,8,7,4,5]

Example 2:

	Input:
	[
	  [1, 2, 3, 4],
	  [5, 6, 7, 8],
	  [9,10,11,12]
	]
	Output: [1,2,3,4,8,12,11,10,9,5,6,7]

### 54.2 Analysis

对于这种螺旋遍历的方法，重要的是要确定上下左右四条边的位置，那么初始化的时候，上边 up 就是0，下边 down 就是 m-1，左边 left 是0，右边 right 是 n-1。然后进行 while 循环，先遍历上边，将所有元素加入结果 res，然后上边下移一位，如果此时上边大于下边，说明此时已经遍历完成了，直接 break。同理对于下边，左边，右边，依次进行相对应的操作，这样就会使得坐标很有规律，并且不易出错。

### 54.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	vector<int> spiral_order(vector<vector<int>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty())
			return {};
		vector<int> res;
		int m = matrix.size(), n = matrix[0].size();
		int up = 0, down = m - 1, left = 0, right = n - 1;
		while (true) {
			for (int j = left; j <= right; j++)
				res.push_back(matrix[up][j]);
			if (++up > down)
				break;
			for (int i = up; i <= down; i++)
				res.push_back(matrix[i][right]);
			if (--right < left)
				break;
			for (int j = right; j >= left; j--)
				res.push_back(matrix[down][j]);
			if (--down < up)
				break;
			for (int i = down; i >= up; i--)
				res.push_back(matrix[i][left]);
			if (++left > right)
				break;
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<vector<int>> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
		};
		vector<int> res = spiral_order(matrix);
		for (int val : res)
			cout << val << " ";
		cout << endl;
	}

## 55. N-Queens II

### 55.1 Description

Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

Example 1:

	Input: [2,3,1,1,4]
	Output: true
	Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

	Input: [3,2,1,0,4]
	Output: false
	Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is
		0, which makes it impossible to reach the last index.

### 55.2 Analysis

这道题说的是有一个非负整数的数组，每个数字表示在当前位置的最大跳力（这里的跳力指的是在当前位置为基础上能到达的最远位置），求判断能不能到达最后一个位置。

我们只对最远能到达的位置感兴趣，所以维护一个变量 reach，表示最远能到达的位置，初始化为0。遍历数组中每一个数字，如果当前坐标大于 reach 或者 reach 已经抵达最后一个位置则跳出循环，否则就更新 reach 的值为其和 i + nums[i] 中的较大值，其中 i + nums[i] 表示当前位置能到达的最大位置。

### 55.3 Code

**1.Solution 1**

	bool can_jump(vector<int> &nums)
	{
		int n = nums.size(), reach = 0;
		for (int i = 0; i < n; i++) {
			if ((i > reach) || (reach >= n - 1))
				break;
			reach = max(reach, i + nums[i]);
		}
		return reach >= n - 1;
	}
	//测试程序
	int main()
	{
		vector<int> nums1{ 2,3,1,1,4 };
		vector<int> nums2{ 3,2,1,0,4 };
		cout << boolalpha << can_jump(nums1) << endl;
		cout << boolalpha << can_jump(nums2) << endl;
	}

## 56. Merge Intervals

### 56.1 Description

### 56.2 Analysis

### 56.3 Code

**1.Solution 1**

## 57. Insert Intervals

### 57.1 Description

### 57.2 Analysis

### 57.3 Code

**1.Solution 1**

## 58. Length of Last Word

### 58.1 Description

Given a string  s  consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string. If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

Example:

	Input: "Hello World"
	Output: 5

### 58.2 Analysis

先对输入字符串做预处理，去掉开头和结尾的空格，然后用一个计数器来累计非空格的字符串的长度，遇到空格则将计数器清零。

### 58.3 Code

**1.Solution 1**

	#include <iostream>
	#include <string>
	using namespace std;

	int length_of_last_word(string s)
	{
		int left = 0, right = s.size() - 1, res = 0;
		while (s[left] == ' ')
			left++;
		while (s[right] == ' ')
			right--;
		for (int i = left; i <= right; i++) {
			if (s[i] == ' ')
				res = 0;
			else
				res++;
		}
		return res;
	}
	//程序测试
	int main()
	{
		string s = "hello world";
		cout << length_of_last_word(s) << endl;
	}

## 59. Spiral Matrix II

### 59.1 Description

Given a positive integer  n , generate a square matrix filled with elements from 1 to  n 2 in spiral order.

Example:

	Input: 3
	Output:
	[
	 [ 1, 2, 3 ],
	 [ 8, 9, 4 ],
	 [ 7, 6, 5 ]
	]

### 59.2 Analysis

分析和"54 Spiral Matrix"相似.

### 59.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	using namespace std;

	vector<vector<int>> generate_matrix(int n)
	{
		vector<vector<int>> res(n, vector<int>(n));
		int up = 0, down = n - 1, left = 0, right = n - 1, val = 1;
		while (true) {
			for (int j = left; j <= right; j++)
				res[up][j] = val++;
			if (++up > down)
				break;
			for (int i = up; i <= down; i++)
				res[i][right] = val++;
			if (--right < left)
				break;
			for (int j = right; j >= left; j--)
				res[down][j] = val++;
			if (--down < up)
				break;
			for (int i = down; i >= up; i--)
				res[i][left] = val++;
			if (++left > right)
				break;
		}
		return res;
	}
	//测试程序
	int main()
	{
		vector<vector<int>> res = generate_matrix(3);
		for (vector<int> vec : res) {
			for (int val : vec)
				cout << val << " ";
			cout << endl;
		}
	}

## 60. Permutation Sequence

### 60.1 Description

The set [1,2,3,..., _n_ ] contains a total of  n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n  = 3:

	"123"
	"132"
	"213"
	"231"
	"312"
	"321"

Given  n  and  k , return the  k th permutation sequence.

Note:

	Given  n  will be between 1 and 9 inclusive.
	Given  k  will be between 1 and  n! inclusive.

Example 1:

	Input: n = 3, k = 3
	Output: "213"

Example 2:

	Input: n = 4, k = 9
	Output: "2314"

### 60.2 Analysis

当n = 3时，其排列组合共有3! = 6种，当n = 4时，其排列组合共有4! = 24种，我们就以n = 4, k = 17的情况来分析，所有排列组合情况如下：

	1234
	1243
	1324
	1342
	1423
	1432
	2134
	2143
	2314
	2341
	2413
	2431
	3124
	3142
	3214
	3241
	3412 <--- k = 17
	3421
	4123
	4132
	4213
	4231
	4312
	4321

我们可以发现，每一位上1,2,3,4分别都出现了6次，当最高位上的数字确定了，第二高位每个数字都出现了2次，当第二高位也确定了，第三高位上的数字都只出现了1次，当第三高位确定了，那么第四高位上的数字也只能出现一次，下面我们来看k = 17这种情况的每位数字如何确定，由于k = 17是转化为数组下标为16：

最高位可取1,2,3,4中的一个，每个数字出现3！= 6次（因为当最高位确定了，后面三位可以任意排列，所以是3！，那么最高位的数字就会重复3！次），所以k = 16的第一位数字的下标为16 / 6 = 2，在 "1234" 中即3被取出。这里我们的k是要求的坐标为k的全排列序列，我们定义 k' 为当最高位确定后，要求的全排序列在新范围中的位置，同理，k'' 为当第二高为确定后，所要求的全排列序列在新范围中的位置，以此类推，下面来具体看看：

第二位此时从1,2,4中取一个，k = 16，则此时的 k' = 16 % (3!) = 4，注意思考这里为何要取余，如果对这24个数以6个一组来分，那么k=16这个位置就是在第三组（k/6 = 2）中的第五个（k%6 = 4）数字。如下所示，而剩下的每个数字出现2！= 2次，所以第二数字的下标为4 / 2 = 2，在 "124" 中即4被取出。

	3124
	3142
	3214
	3241
	3412 <--- k' = 4
	3421

第三位此时从1,2中去一个，k' = 4，则此时的k'' = 4 % (2!) = 0，如下所示，而剩下的每个数字出现1！= 1次，所以第三个数字的下标为 0 / 1 = 0，在 "12" 中即1被取出。

	3412 <--- k'' = 0
	3421

第四位是从2中取一个，k'' = 0，则此时的k''' = 0 % (1!) = 0，如下所示，而剩下的每个数字出现0！= 1次，所以第四个数字的下标为0 / 1= 0，在 "2" 中即2被取出。

	3412 <--- k''' = 0

那么我们就可以找出规律了

	a1 = k / (n - 1)!
	k1 = k
	
	a2 = k1 / (n - 2)!
	k2 = k1 % (n - 2)!
	...
	
	an-1 = kn-2 / 1!
	kn-1 = kn-2 % 1!
	
	an = kn-1 / 0!
	kn = kn-1 % 0!

### 60.3 Code

**1.Solution 1**

	#include <iostream>
	#include <vector>
	#include <string>
	using namespace std;

	string get_permutation(int n, int k)
	{
		string res;
		string num = "123456789";
		vector<int> f(n, 1);
		for (int i = 1; i < n; i++)
			f[i] = f[i - 1] * i;
		k--;
		for (int i = n; i >= 1; i--) {
			int j = k / f[i - 1];
			k %= f[i - 1];
			res.push_back(num[j]);
			num.erase(j, 1);
		}
		return res;
	}
	//测试程序
	int main()
	{
		cout << get_permutation(4, 17);
	}

## 61. Rotate List

### 61.1 Description

Given a list, rotate the list to the right by  k  places, where  k  is non-negative.

For example:

	Given 1->2->3->4->5->NULL and  k  = 2,
	return 4->5->1->2->3->NULL.

### 61.2 Analysis

用快慢指针来解，快指针先走k步，然后两个指针一起走，当快指针走到末尾时，慢指针的下一个位置是新的顺序的头结点，这样就可以旋转链表了，自信满满的写完程序，放到OJ上跑，以为能一次通过，结果跪在了各种特殊情况，首先一个就是当原链表为空时，直接返回NULL，还有就是当k大于链表长度和k远远大于链表长度时该如何处理，我们需要首先遍历一遍原链表得到链表长度n，然后k对n取余，这样k肯定小于n。

### 61.3 Code

**1.Solution 1**

	#include <iostream>
	using namespace std;

	struct list_node {
		int val;
		list_node *next;
		list_node(int v) :
			val(v),
			next(nullptr)
		{}
	};

	list_node *rotate_right(list_node *head, int k)
	{
		if (!head)
			return nullptr;
		int n = 0;
		list_node *cur = head;
		while (cur) {
			n++;	
			cur = cur->next;
		}
		k %= n;
		list_node *fast = head, *slow = head;
		for (int i = 0; i < k; i++) {
			if (fast)
				fast = fast->next;
		}
		if (!fast)
			return head;
		fast->next = slow;
		fast = slow->next;
		slow->next = nullptr;
		return fast;
	}
	//测试程序
	int main()
	{
		list_node *l1 = new list_node(1);
		list_node *res;
	
		list_node *cur = l1;
		cur->next = new list_node(2);
		cur = cur->next;
		cur->next = new list_node(3);
		cur = cur->next;
		cur->next = new list_node(4);
		cur = cur->next;
		cur->next = new list_node(5);
	
		res = rotate_right(l1, 2);
		while (res) {
			cout << res->val << "->";
			res = res->next;
		}
		cout << "nullptr" << endl;
	}

## 62. Unique Paths

### 62.1 Description

![](images/unique_paths_1.png)

A robot is located at the top-left corner of a  m  x  n  grid (marked 'Start' in the diagram below). The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below). How many possible unique paths are there?

Above is a 7 x 3 grid. How many possible unique paths are there?
Note:  m  and  n  will be at most 100.

Example 1:

	Input: m = 3, n = 2
	Output: 3
	Explanation:
	From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
	1.Right -> Right -> Down
	2.Right -> Down -> Right
	3.Down -> Right -> Right

Example 2:

	Input: m = 7, n = 3
	Output: 28

### 62.2 Analysis

每次可以向下走或者向右走,求到达最右下角的所有不同走法的个数.需要用动态规划Dynamic Programming来解,可以维护一个二维数组dp,其中dp[i][j]表示到当前位置不同的走法的个数,然后可以得到状态转移方程为:dp[i][j]=dp[i-1][j] +dp[i][j-1],这里为了节省空间,使用一维数组dp,一行一行的刷新也可以.

### 62.3 Code

	#include <iostream>
	using namespace std;

	int unique_paths(int m, int n)
	{
		vector<int> dp(n ,1);
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[j] += dp[j - 1];
			}
		}
		return dp[n - 1];
	}
	//测试程序
	int main()
	{
		cout << unique_paths(3, 2);	//结果为3.
	}
	PS:该题的代码分析为:(dp[j] = dp[j - 1])
	1	1	1	1	1	1
		|	|	|	|	|
	1--	2--	3--	4--	5--	6
		|	|	|	|	|
	1--	3--	6--	10--15--21

## 63. Unique Paths II

### 63.1 Description

A robot is located at the top-left corner of a  m  x  n  grid (marked 'Start' in the diagram below). The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below). Now consider if some obstacles(障碍) are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid. Note:  m  and  n  will be at most 100.

Example 1:

	Input:
	[
	  [0,0,0],
	  [0,1,0],
	  [0,0,0]
	]
	Output: 2
	Explanation:
	There is one obstacle in the middle of the 3x3 grid above.
	There are two ways to reach the bottom-right corner:
	1.Right -> Right -> Down -> Down
	2.Down -> Down -> Right -> Right

### 63.2 Analysis

每次可以向下走或者向右走,求到达最右下角的所有不同走法的个数.需要用动态规划Dynamic Programming来解,可以维护一个二维数组dp,其中dp[i][j]表示到当前位置不同的走法的个数,然后可以得到状态转移方程为:dp[i][j]=dp[i-1][j] +dp[i][j-1],这里为了节省空间,使用一维数组dp,一行一行的刷新也可以.当某个位置是障碍物时,其dp值为0,直接跳过该位置即可.这里还需要初始化dp数组的某个值,使得其能正常累加.当起点不是障碍物时,其dp值应该为1,即dp[1][1]=1,由于其是由dp[0][1]+dp[1][0]更新而来,所以二者中任意一个初始化为1即可.

### 63.3 Code

	#include <iostream>
	#include <vector>
	using namespace std;
	
	int unique_path_with_obstacles(vector<vector<int>> &obstacle_grid)
	{
		if (obstacle_grid.empty() || obstacle_grid[0].empty() || obstacle_grid[0][0] == 1)
			return 0;
	
		int m = obstacle_grid.size(), n = obstacle_grid[0].size();
		vector<int> dp(n, 0);
		dp[0] = 1;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (obstacle_grid[i][j] == 1)
					dp[j] = 0;
				else if (j > 0)
					dp[j] += dp[j - 1];
			}
		}
		return dp[n - 1];
	}
	
	int main()
	{
		vector<vector<int>> obstacle_grid = {
			{0, 0, 0},
			{0, 1, 0},
			{0, 0, 0}
		};
		cout << unique_path_with_obstacles(obstacle_grid) << endl;
		return 0;
	}
	/*
		编译:g++ test.cpp -o test -std=c++0x
		结果为:2
	PS:该题的代码分析为:(dp[j] = dp[j - 1])
	0--	0--	0
	|		|
	0	1	0
	|		|
	0--	0--	0	//总共2条路

## 64. Unique Paths II

### 64.1 Description

Given a  m  x  n  grid filled with non-negative numbers, find a path from top left to bottom right which  minimizes  the sum of all numbers along its path. Note: You can only move either down or right at any point in time.

Example:

	Input:
	[
	  [1,3,1],
	  [1,5,1],
	  [4,2,1]
	]
	Output: 7
	Explanation: Because the path 1→3→1→1→1 minimizes the sum.

### 64.2 Analysis

这道题给了我们一个只有非负数的二维数组，让找一条从左上到右下的路径，使得路径和最小，限定了每次只能向下或者向右移动。一个常见的错误解法就是每次走右边或下边数字中较小的那个，这样的贪婪算法获得的局部最优解不一定是全局最优解，因此是不行的。实际上这道题需要用动态规划 Dynamic Programming 来做，我们维护一个二维的 dp 数组，其中 dp[i][j] 表示到达当前位置的最小路径和。接下来找状态转移方程，因为到达当前位置 (i, j)  只有两种情况，要么从上方 (i-1, j) 过来，要么从左边 (i, j-1) 过来，我们选择 dp 值较小的那个路径，即比较 dp[i-1][j] 和 dp[i][j-1]，将其中的较小值加上当前的数字 grid[i][j]，就是当前位置的 dp 值了。但是有些特殊情况要提前赋值，比如起点位置，直接赋值为 grid[0][0]，还有就是第一行和第一列，其中第一行的位置只能从左边过来，第一列的位置从能从上面过来，所以这两行要提前初始化好，然后再从 (1, 1) 的位置开始更新到右下角即可.

### 64.3 Code

	#include <iostream>
	#include <vector>
	#include <algorithm>
	using namespace std;
	
	int min_path_sum(vector<vector<int>> &grid)
	{
		if (grid.empty() || grid[0].empty())
			return 0;
		int m = grid.size(), n = grid[0].size();
		vector<vector<int>> dp(m, vector<int>(n));
		dp[0][0] = grid[0][0];
		for (int i = 1; i < m; i++)
			dp[i][0] = grid[i][0] + dp[i - 1][0];
		for (int j = 1; j < n; j++)
			dp[0][j] = grid[0][j] + dp[0][j - 1];
	
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		return dp[m-1][n-1];
	}
	
	int main()
	{
		vector<vector<int>> grid = {
			{1, 3, 1},
			{1, 5, 1},
			{4, 2, 1}
		};
		cout << min_path_sum(grid) << endl;
		return 0;
	}
	/*
		编译:g++ test.cpp -o test -std=c++0x
		结果:7
	*/


## 65. Valid number

### 65.1 Description

### 65.2 Analysis

### 65.3 Code

## 66. Plus One

### 66.1 Description

Given a non-negative number represented as an array of digits, plus one to the number. The digits are stored such that the most significant digit is at the head of the list.

### 66.2 Analysis

将一个数字的每个位上的数字分别存到一个一维向量中，最高位在最开头，我们需要给这个数字加一，即在末尾数字加一，如果末尾数字是9，那么则会有进位问题，而如果前面位上的数字仍为9，则需要继续向前进位。具体算法如下：首先判断最后一位是否为9，若不是，直接加一返回，若是，则该位赋0，再继续查前一位，同样的方法，直到查完第一位。如果第一位原本为9，加一后会产生新的一位，那么最后要做的是，查运算完的第一位是否为0，如果是，则在最前头加一个1。

### 66.3 Code

	#include <iostream>
	#include <vector>
	#include <algorithm>
	using namespace std;
	
	vector<int> plus_one(vector<int> &digits)
	{
		int n = digits.size();
		for (int i = n - 1; i >= 0; i--) {
			if (digits[i] == 9)
				digits[i] = 0;
			else {
				digits[i] += 1;
				return digits;
			}
		}
		digits.insert(digits.begin(), 1);
		return digits;
	}
	
	int main()
	{
		vector<int> digits = {9, 9, 9, 9};
		vector<int> results = plus_one(digits);
		for (int num : results) {
			cout << num << " ";
		}
		cout << endl;
	}
	/*
		编译:g++ test.cpp -o test -std=c++0x
		结果:1 0 0 0 0
	*/

## 67. Add Binary

### 67.1 Description

Given two binary strings, return their sum (also a binary string).

For example,

	a = "11"
	b = "1"
	Return "100".

### 67.2 Analysis

二进制数相加，并且保存在string中，要注意的是如何将string和int之间互相转换，并且每位相加时，会有进位的可能，会影响之后相加的结果。而且两个输入string的长度也可能会不同。这时我们需要新建一个string，它的长度是两条输入string中的较大的那个，并且把较短的那个输入string通过在开头加字符‘0’来补的较大的那个长度。这时候我们逐个从两个string的末尾开始取出字符，然后转为数字相加，如果大于等于2，则标记进位标志carry，并且给新string加入一个字符'0'。

### 67.3 Code

	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	using namespace std;
	
	string add_binary(string a, string b)
	{
		string res;
		int na = a.size();
		int nb = b.size();
		int n = max(na, nb);
		bool carry = false;
		if (na > nb) {
			for (int i = 0; i < (na - nb); i++)
				b.insert(b.begin(), '0');
		} else if (na < nb) {
			for (int i = 0; i < (nb - na); i++)
				a.insert(a.begin(), '0');
		}
	
		for (int i = n - 1; i >= 0; i--) {
			int tmp = 0;
			if (carry)
				tmp = (a[i] - '0') + (b[i] - '0') + 1;
			else
				tmp = (a[i] - '0') + (b[i] - '0');
	
			if (tmp == 0) {
				res.insert(res.begin(), '0');
				carry = false;
			} else if (tmp == 1) {
				res.insert(res.begin(), '1');
				carry = false;
			} else if (tmp == 2) {
				res.insert(res.begin(), '0');
				carry = true;
			} else if (tmp == 3) {
				res.insert(res.begin(), '1');
				carry = true;
			}
		}
	
		if (carry)
			res.insert(res.begin(), '1');
		return res;
	}
	
	int main()
	{
		string a = "11";
		string b = "1";
		cout << add_binary(a, b) << endl;
	}
	/*
		编译:g++ test.cpp -o test -std=c++0x -g	//挂gdb编译
			gdb test
			b 10
			r
		结果:100
	*/

## 68. Text Justification

### 68.1 Description

### 68.2 Analysis

### 68.3 Code

## 69. sqrt(x)

### 69.1 Description

Implement int sqrt(int x). Compute and return the square root of  x.

### 69.2 Analysis

这道题要求我们求平方根,使用牛顿迭代法.牛顿迭代法如下:

计算x^2 = n的解，令f(x)=x^2-n，相当于求解f(x)=0的解.

	1.首先取x0,如果x0不是解,做一个经过(x0,f(x0))这个点的切线,与x轴的交点为x1;
	2.同样的道理，如果x1不是解，做一个经过(x1,f(x1))这个点的切线，与x轴的交点为x2,以此类推;
	3.以这样的方式得到的xi会无限趋近于f(x)=0的解.
	判断xi是否是f(x)=0的解有两种方法：
		1.直接计算f(xi)的值判断是否为0;
		2.二是判断前后两个解xi和xi-1是否无限接近.
	经过(xi, f(xi))这个点的切线方程为f(x)=f(xi)+f'(xi)(x-xi),其中f'(x)为f(x)的导数,本题中为2x.
	令切线方程等于0,即可求出xi+1=xi-f(xi)/f'(xi).
	继续化简:
	xi+1=xi-(xi^2-n)/(2xi)=xi-xi/2+n/(2xi)=xi/2+n/2xi=(xi+n/xi)/2.

### 69.3 Code

	// x:为n的值
	double my_sqrt(double x)
	{
		if (x == 0)
			return 0;
		double res = 1.0, pre = 0.0;
		while (abs(res - pre) > 1e-6) {
			pre = res;
			res = (res + x / res) / 2;
		}
		return res;
	}

	int main()
	{
		cout << my_sqrt(0.5);
	}
	//结果为:0.25

## 70. Climbing stairs

### 70.1 Description

You are climbing a stair case. It takes  n  steps to reach to the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? Note: Given  n  will be a positive integer.

Example 1:

	Input: 2
	Output: 2
	Explanation: There are two ways to climb to the top.
	1.1 step + 1 step
	2.2 steps

Example 2:

	Input: 3
	Output: 3
	Explanation: There are three ways to climb to the top.
	1.1 step + 1 step + 1 step
	2.1 step + 2 steps
	3.2 steps + 1 step

### 70.2 Analysis

假设梯子有n层，那么如何爬到第n层呢，因为每次只能爬1或2步，那么爬到第n层的方法要么是从第 n-1 层一步上来的，要不就是从 n-2 层2步上来的，所以递推公式非常容易的就得出了：dp[n] = dp[n-1] + dp[n-2]。 斐波那契额数列的求解可以用递归，但是递归放到OJ上运行，会显示 Time Limit Exceeded，就是说运行时间超了，因为递归计算了很多分支，效率很低，这里需要用动态规划 (Dynamic Programming) 来提高效率，代码如下。

### 70.3 Code

	#include <iostream>
	#include <vector>
	using namespace std;

	int climb_stairs(int n)
	{
		if (n <= 1)
			return 1;
		vector<int> dp(n);
		dp[0] = 1, dp[1] = 2;
		for (int i = 2; i < n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp.back();
	}
	int main()
	{
		cout << climb_stairs(5);
	}

## 71. Simplify path

### 71.1 Description

Given an absolute path for a file (Unix-style), simplify it.
For example,

	path = "/home/", => "/home"
	path = "/a/./b/../../c/", => "/c"

click to show corner cases.Corner Cases:

	1.Did you consider the case where path = "/../"?
	In this case, you should return "/".
	2.Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
	In this case, you should ignore redundant slashes and return "/home/foo".

### 71.2 Analysis

这道题让简化给定的路径，加上两个例子 path = "/a/./b/../c/", => "/a/c"和path = "/a/./b/c/", => "/a/b/c"， 这样我们就可以知道中间是"."的情况直接去掉，是".."时删掉它上面挨着的一个路径，而下面的边界条件给的一些情况中可以得知，如果是空的话返回"/"，如果有多个"/"只保留一个。那么我们可以把路径看做是由一个或多个"/"分割开的众多子字符串，把它们分别提取出来一一处理即可，代码如下.

### 71.3 Code

	#include <iostream>
	#include <sstream>
	#include <string>
	using namespace std;

	string simplify_path(string path)
	{
		string res, t;
		stringstream ss(path);
		vector<string> v;
		while (getline(ss, t, '/')) {
			if ((t == "") || (t == "."))
				continue;
			if ((t == "..") && (!v.empty()))
				v.pop_back();
			else if (t != "..")
				v.push_back(t);
		}
		for (string s : v)
			res += "/" + s;
		return res.empty() ? "/" : res;
	}

	int main()
	{
		cout << simplify("/a/./b/../../c/");
	}

## 72. Edit distance

### 72.1 Description

### 72.2 Analysis

### 72.3 Code

## 73. Set Matrix Zeroes

### 73.1 Description

Given a  m  x  n  matrix, if an element is 0, set its entire row and column to 0. Do it in place.

Follow up:

	Did you use extra space?
	A straight forward solution using O( m n ) space is probably a bad idea.
	A simple improvement uses O( m  +  n ) space, but still not the best solution.
	Could you devise a constant space solution?

example 1:

![](images/matrix_zeroes.png)

	Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
	Output: [[1,0,1],[0,0,0],[1,0,1]]

example 2:

![](images/matrix_zeroes_2.png)

	Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
	Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

### 73.2 Analysis

新建一个和matrix等大小的矩阵，然后一行一行的扫，只要有0，就将新建的矩阵的对应行全赋0，行扫完再扫列，然后把更新完的矩阵赋给matrix即可，这个算法的空间复杂度太高。将其优化到O(m+n)的方法是，用一个长度为m的一维数组记录各行中是否有0，用一个长度为n的一维数组记录各列中是否有0，最后直接更新matrix数组即可。这道题的要求是用O(1)的空间，那么我们就不能新建数组，我们考虑就用原数组的第一行第一列来记录各行各列是否有0.

	先扫描第一行第一列，如果有0，则将各自的flag设置为true
	然后扫描除去第一行第一列的整个数组，如果有0，则将对应的第一行和第一列的数字赋0
	再次遍历除去第一行第一列的整个数组，如果对应的第一行和第一列的数字有一个为0，则将当前值赋0
	最后根据第一行第一列的flag来更新第一行第一列

### 73.3 Code

	#include <iostream>
	#include <vector>

	void set_zeroes(vector<vector<int>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty())
			return;

		int m = matrix.size(), n = matrix[0].size();
		bool row_zero = false, col_zero = false;
		for (int i = 0; i < m; i++) {
			if (matrix[i][0] == 0)
				col_zero = true;
		}
		for (int j = 0; j < n; j++) {
			if (matrix[0][j] == 0)
				row_zero = true;
		}

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (matrix[0][j] == 0 || matrix[i][0] == 0)
					matrix[i][j] = 0;
			}
		}

		if (row_zero) {
			for (int j = 0; j < n; j++)
				matrix[0][j] = 0;
		}
		if (col_zero) {
			for (int i = 0; i < m; i++)
				matrix[i][0] = 0;
		}
	}

	int main()
	{
		vector<vector<int>> matrix = {
			{0, 1, 2, 0},
			{3, 4, 5, 2},
			{1, 3, 1, 5}
		};

		set_zeroes(matrix);
		for (vector<int> vec : matrix) {
			cout << "{";
			for (int val : vec) {
				cout << val << ",";
			}
			cout << "}" << end;
		}
	}

## 74. Search a 2D matrix

### 74.1 Description

Write an efficient algorithm that searches for a value in an  m  x  n  matrix. This matrix has the following properties:
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

Example 1:

	Input:
	matrix = [
	  [1,   3,  5,  7],
	  [10, 11, 16, 20],
	  [23, 30, 34, 50]
	]
	target = 3
	Output: true

Example 2:
	
	Input:
	matrix = [
	  [1,   3,  5,  7],
	  [10, 11, 16, 20],
	  [23, 30, 34, 50]
	]
	target = 13
	Output: false

### 74.2 Analysis

这道题要求搜索一个二维矩阵，由于给的矩阵是有序的，所以很自然的想到要用二分查找法，可以在第一列上先用一次二分查找法找到目标值所在的行的位置，然后在该行上再用一次二分查找法来找是否存在目标值。

### 74.3 Code

	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	using namespace std;
	
	bool search_matrix(vector<vector<int>> matrix, int target)
	{
		if (matrix.empty() || matrix[0].empty())
			return false;
	
		int m = matrix.size(), n = matrix[0].size();
		int up_pos = 0, down_pos = matrix.size();
		
		while (up_pos < down_pos) {
			int mid_pos = (up_pos + down_pos) / 2;
			if (matrix[mid_pos][0] == target)
				return true;
			if (matrix[mid_pos][0] < target)
				up_pos = mid_pos + 1;
			else
				down_pos = mid_pos;
		}
	
		int row = (right > 0) ? (down_pos - 1) : down_pos;
		int left = 0, right = matrix[row].size();
		while (left < right) {
			int mid = (left + right) / 2;
			if (matrix[row][mid] == target)
				return true;
			if (matrix[row][mid] < target)
				left = mid + 1;
			else
				right = mid;
		}
		return false;
	}
	
	
	int main()
	{
		vector<vector<int>> matrix = {
			{1,   3,  5,  7},
			{10, 11, 16, 20},
			{23, 30, 34, 50}
		};
	
		cout << boolalpha << search_matrix(matrix, 3) << endl;
	}
	//结果为:true

## 75. Sort colors

### 75.1 Description

Given an array with  n  objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
Note: You are not suppose to use the library's sort function for this problem.

	Example:
	
	Input: [2,0,2,1,1,0]
	Output: [0,0,1,1,2,2]

Follow up:

A rather straight forward solution is a two-pass algorithm using counting sort.  
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
Could you come up with a one-pass algorithm using only constant space?

### 75.2 Analysis

首先遍历一遍原数组，分别记录 0，1，2 的个数。然后更新原数组，按个数分别赋上 0，1，2。

### 75.3 Code

	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	using namespace std;
	
	void sort_colors(vector<int> &nums)
	{
		vector<int> colors(3, 0);
		for (int val : nums)
			colors[val]++;
	
		for (int i = 0, cur = 0; i < 3; i++) {
			for (int j = 0; j < colors[i]; j++) {
				nums[cur++] = i;
			}
		}
	}
	
	
	int main()
	{
		vector<int> numbers = {2,0,2,1,1,0};
		sort_colors(numbers);
		for (int val : numbers)
			cout << val << ",";
	
		cout << endl;
	}
	//结果为:0,0,1,1,2,2,

## 76. Minimum Window Substring

### 76.1 Description

### 76.2 Analysis

### 76.3 Code

## 77. Combinations

### 77.1 Description

Given two integers  n  and  k , return all possible combinations of  k  numbers out of 1 ...  n.

For example,
	If  n  = 5 and  k  = 3, a solution is:
	1 2 3
	1 2 4
	1 2 5
	1 3 4
	1 3 5
	1 4 5
	2 3 4
	2 3 5
	2 4 5
	3 4 5

### 77.2 Analysis

这道题让求1到n共n个数字里k个数的组合数的所有情况，还是要用深度优先搜索DFS调用递归来解。那么我们建立一个保存最终结果的大集合res，还要定义一个保存每一个组合的小集合out，每次放一个数到out里，如果out里数个数到了k个，则把out保存到最终结果中，否则在下一层中继续调用递归。

### 77.3 Code

	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	using namespace std;
	
	void helper(int n, int k, int level, vector<int> &out, vector<vector<int>> &res)
	{
		if (out.size() == k) {
			res.push_back(out);
			return;
		}
		for (int i = level; i <= n; i++) {
			out.push_back(i);
			helper(n, k, i, out, res);
			out.pop_back();
		}
	}
	
	vector<vector<int>> combine(int n, int k)
	{
		vector<vector<int>> res;
		vector<int> out;
		helper(n, k, 1, out, res);
		return res;
	}
	
	int main()
	{
		vector<vector<int>> res = combine(4, 2);
		for (vector<int> vec : res) {
			cout << "[ ";
			for (int val : vec) {
				cout << val << " ";
			}
			cout << "]," << endl;
		}
	}
	//结果为:
	[ 1 1 ],
	[ 1 2 ],
	[ 1 3 ],
	[ 1 4 ],
	[ 2 2 ],
	[ 2 3 ],
	[ 2 4 ],
	[ 3 3 ],
	[ 3 4 ],
	[ 4 4 ],

## 78. Subsets

### 78.1 Description

Given a set of distinct integers,  S , return all possible subsets.

Note:

Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
 

For example,
	If  S  = [1,2,3], a solution is:
	
	[
	  [3],
	  [1],
	  [2],
	  [1,2,3],
	  [1,3],
	  [2,3],
	  [1,2],
	  []
	]

### 78.2 Analysis

这道求子集合的问题，由于其要列出所有结果，按照以往的经验，肯定要是要用递归来做。这道题其实它的非递归解法相对来说更简单一点，下面我们先来看非递归的解法，由于题目要求子集合中数字的顺序是非降序排列的，所有我们需要预处理，先给输入数组排序，然后再进一步处理，最开始我在想的时候，是想按照子集的长度由少到多全部写出来，比如子集长度为0的就是空集，空集是任何集合的子集，满足条件，直接加入。下面长度为1的子集，直接一个循环加入所有数字，子集长度为2的话可以用两个循环，但是这种想法到后面就行不通了，因为循环的个数不能无限的增长，所以我们必须换一种思路。我们可以一位一位的往上叠加，比如对于题目中给的例子 [1,2,3] 来说，最开始是空集，那么我们现在要处理1，就在空集上加1，为 [1]，现在我们有两个自己 [] 和 [1]，下面我们来处理2，我们在之前的子集基础上，每个都加个2，可以分别得到 [2]，[1, 2]，那么现在所有的子集合为 [], [1], [2], [1, 2]，同理处理3的情况可得 [3], [1, 3], [2, 3], [1, 2, 3], 再加上之前的子集就是所有的子集合了.

### 78.3 Code

	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	using namespace std;
	
	vector<vector<int>> subset(vector<int> &s)
	{
		vector<vector<int>> res(1);
		sort(s.begin(), s.end());
		for (int i = 0; i < s.size(); i++) {
			int size = res.size();
			for (int j = 0; j < size; j++) {
				res.push_back(res[j]);
				res.back().push_back(s[i]);
			}
		}
		return res;
	}
	
	int main()
	{
		vector<int> s = {1, 2, 3};
		vector<vector<int>> res = subset(s);
		for (vector<int> vec : res) {
			cout << "[ ";
			for (int val : vec) {
				cout << val << " ";
			}
			cout << "]," << endl;
		}
	}
	//结果为:
	[ ],
	[ 1 ],
	[ 2 ],
	[ 1 2 ],
	[ 3 ],
	[ 1 3 ],
	[ 2 3 ],
	[ 1 2 3 ],

## 79. word search

### 79.1 Description

### 79.2 Analysis

### 79.3 Code