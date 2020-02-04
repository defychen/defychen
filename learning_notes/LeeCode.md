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

### 12.2 Analysis

### 12.3 Code

## 13. Roman to Integer

### 13.1 Description

### 13.2 Analysis

### 13.3 Code