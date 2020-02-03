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