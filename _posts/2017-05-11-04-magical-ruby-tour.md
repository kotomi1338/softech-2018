---
layout: post
title:  "04 Rubyツアー その1"
date:   2017-05-11 12:00:00 +0900

---

## はじめに

ではさっそく、Rubyでプログラムを書いていくための基礎知識を見ていきましょう。irbを使って動作を確認したり、後々のためにコードをファイルとして保存しても結構ですし、さらっと読み進めて練習問題に進んでもかまいません。

コード例は、以下のように記述します。必要に応じてirbで実行した時の結果を示すこともあり、その事を示す行は #=> で始まっています。

{% highlight ruby linenos %}
name = "Takuya"
#=> "Takuya"
age = 21
#=> 21

puts "#{name} is #{age} years old."
#=> Takuya is 21 years old.
{% endhighlight %}

なお今年は、「プログラミングの基礎」そのものよりも、「プログラミングで何か作ること」に焦点を当てたいので、昨年のように言語の各仕様について時間を使って学んでいくということはしない予定です。


## 基本編

### コメント

C言語でのコメントは // や /* ~ */ でしたが、Rubyの場合は#です。ある行について、#より後はすべてコメントとして扱われます。

{% highlight ruby linenos %}
puts "Hello" # これはコメントです。
# これもコメントです。
{% endhighlight %}


### 変数を使う

データを保持するために変数を使います。Rubyでは、変数を使うために宣言したり、型を指定する必要はありません。

{% highlight ruby linenos %}
name = "Takuya" # 文字列型
age = 21        # 整数型
height = 166.9  # 実数型
# 他にもいろいろ
{% endhighlight %}

変数名は、アルファベット大文字で始まってはいけないというルールがあります。

### 四則演算

次のようにして数値の計算をすることができます。

{% highlight ruby linenos %}
japanese = 71
math = 98
science = 60
sum = japanese + math + science
#=> 229

ave = sum / 3 # 整数同士の割り算なので結果も整数
#=> 76

ave = sum / 3.0 # 実数の値が欲しいなら、実数の割り算にする
#=> 76.33333333333333
{% endhighlight %}

その他、引き算や掛け算、剰余算もC言語と同様にできます。

### クラス（型）を調べる

人間がわざわざ型を指定して変数を宣言する必要が無いというだけで、Rubyのデータはきちんとクラス（型）を持っています。先程上げた変数や数値、文字列はすべてRubyでは「オブジェクト」として存在し、オブジェクトの種類は「クラス」で表されます。

オブジェクトのクラスは以下のようにして調べることができます。

{% highlight ruby linenos %}
1.class
#=> Integer
3.14.class
#=> Float
"aaa".class
#=> String

name = "Takuya"
name.class
#=> String
age = 3
age.class
#=> Integer
{% endhighlight %}

### 文字列

""や''で囲った表現はすべて文字列とみなされます。文字列は、Stringクラスのオブジェクトです。

{% highlight ruby linenos %}
first_name = "Takuya"
last_name = 'Mukohira'
first_name.class
#=> String
{% endhighlight %}

次のように、+演算子を使って文字列同士を結合することもできます。

{% highlight ruby linenos %}
full_name = last_name + " " + first_name
{% endhighlight %}

""と''はどちらも文字列を表すのに使えますが、""のみ中に値を埋め込んだり、制御文字を\nなどの表現で表すことができます。

{% highlight ruby linenos %}
name = gets()
puts "Hello, #{name}" # Hello, Takuya
puts 'Hello, #{name}' # Hello, #{name}
{% endhighlight %}

なお、C言語では文字列はchar型変数の配列として表現していましたが、Rubyではそのまま文字列として扱うことができます。


### メソッドの呼び出し

オブジェクトには「メソッド」をもたせることができます。メソッドとは、オブジェクトで行うひとかたまりの「処理」に名前をつけたものです。

オブジェクトのメソッドを呼び出す基本の形は、以下のとおりです。

```
obj.method
```

例えば、文字列オブジェクトのメソッドは以下の様なものがあります。

{% highlight ruby linenos %}
name = "Takuya"
name.length()
#=> 6
name.empty?()
#=> false
{% endhighlight %}

また、メソッドの()は解析上困らない場合は省略することができます。

{% highlight ruby linenos %}
str = ""
str.length
#=> 0
str.empty?
#=> true
{% endhighlight %}


### 配列

配列を作るには、次のように書きます。配列は、Arrayクラスのオブジェクトです。基本的な使い方はC言語と同じで、配列の要素は list[0] というように参照できます。

{% highlight ruby linenos %}
list = [1, 2, 3]
list.class
#=> Array
list[0]
#=> 1
list[2] = 0
list
#=> [1, 2, 0]
{% endhighlight %}

また、C言語では配列の長さは固定（要素数3で宣言した配列には、4個目の要素を追加できない）ですが、Rubyの場合は可変です。

{% highlight ruby linenos %}
list2 = [2, 4, 8]
list2.length
#=> 3
list2[3]
#=> nil
list2[3] = 16
list2.length
#=> 4
{% endhighlight %}

Arrayクラスには、配列の操作に使える便利なメソッドがたくさん用意されています。

{% highlight ruby linenos %}
list3 = [1, 2, 3]
list3.size
#=> 3
list.include?(0)
#=> false
list.sample
#=> 1か2か3（配列内の要素がランダムに返される）
{% endhighlight %}

また、配列に対しても演算子を使った演算ができます。

{% highlight ruby linenos %}
# 配列の結合を行う
li1 = [2, 3, 5]
li2 = [7, 11, 13]
li3 = li1 + li2
#=> [2, 3, 5, 7, 11, 13]

# 配列同士の差分を得る
a = [1, 2, 3]
b = [1, 3, 5]
c = a - b
#=> [2]
{% endhighlight %}

C言語では、intで宣言した配列にはintの要素しか格納できませんでしたが、Rubyの配列は、いろいろな型の要素を格納することができます。

{% highlight ruby linenos %}
iroiro_list = [1, 1.5, 'こんにちは', nil]
iroiro_list[0].class
#=> Integer
iroiro_list[1].class
#=> Float
iroiro_list[2].class
#=> String
iroiro_list[3].class
#=> NilClass
{% endhighlight %}


### ハッシュ

ハッシュは、C言語には無い新しい概念です。配列同様、複数のオブジェクトをまとめて扱うことができますが、配列はオブジェクトを順番（添字）で管理するのに対し、ハッシュは名前で管理します。ハッシュは、Hashクラスのオブジェクトです。

{% highlight ruby linenos %}
takuya = { name: 'Takuya', age: 3, gender: 'female' }
takuya.class
#=> Hash
{% endhighlight %}

ハッシュの名前の部分をキー、それに紐づくデータを値と呼びます。ハッシュは以下のようにして特定のキーに紐づく値を呼び出すことができます。  
値が存在しないキーを呼び出すと何もないを表すnilを返します。値が存在しないキーに対して代入を行うこともできます。

{% highlight ruby linenos %}
takuya[:name]
#=> "Takuya"
takuya[:height]
#=> nil
takuya[:height] = 166.9
takuya
#=> { name: 'Takuya', age: 3, gender: 'female', height: 166.9 }
{% endhighlight %}

### 真偽値

プログラムでは、ある条件に当てはまっているかそうでないかを判定することが多々あります。ある条件に当てはまっている時を真(true)、そうでない時を偽(false)といいます。Rubyでは、なにもないことを表すnilとfalse以外の値はすべて真となります。

trueはTrueClass、falseはFalseClass、そしてnilはNilClassのオブジェクトです。

{% highlight ruby linenos %}
true.class
#=> TrueClass
false.class
#=> FalseClass
nil.class
#=> NilClass

ok = true
if ok
  puts "いいよ"
else
  puts "だめ"
end
{% endhighlight %}


## 制御構造編
### 条件分岐

ほぼC言語と同じですが微妙に字面が違ったり、()を省略できたりします。

{% highlight ruby linenos %}
age = 17

if age <= 6
  puts "幼稚園児"
elsif <= 12
  puts "小学生"
elsif <= 15
  puts "中学生"
elsif <= 20
  puts "高専生"
else
  puts "学生じゃないです"
end
#=> 高専生
{% endhighlight %}


### 繰り返し処理とイテレーション

プログラムでは、繰り返し処理を行いたいことがあります。例えば、次のようにいろいろな種類のオブジェクトの入った、配列listがあるとします。

{% highlight ruby linenos %}
list = ['apple', 1, 2, 1.5, { name: 'Takuya' }, nil, true, false]
{% endhighlight %}

このリストの要素を順番に取り出して、クラス名を表示したいとします。以下のコードは、すべてその処理をRubyで書いたものです。なお、オブジェクトの集合の要素を1つずつ順番に参照するような処理のことを、一般的にイテレーションと呼びます。

{% highlight ruby linenos %}
# forを使う
for element in list
  puts element.class
end

# eachメソッドを使う（ブロックをdo - endで表現）
list.each do |element|
  puts element.class
end

# eachメソッドを使う（ブロックを{ - }で表現）
list.each { |element| puts element.class }
{% endhighlight %}

ひとまとまりの処理の事をブロックと言います。Rubyは、do-endまたは{}でブロックを表現することができます。

Rubyでは、ブロックをメソッドの引数にすることができるので、上記のeachメソッドを使った例を言葉で説明すると、「配列オブジェクトの持つeachメソッドに、要素のclassを出力する処理のブロックを渡している。」といえます。

別の例を見てみましょう。nに0から9までを代入して表示をするようなプログラムは、次のように書くことができます。

{% highlight ruby linenos %}
# for文を使う
for n in 0..9
  puts n
end

# 数値オブジェクトのtimesメソッドを使う
10.times do |n|
  puts n
end

# whileを使う
n = 0
while (n < 10)
  puts n
  n += 1
end
{% endhighlight %}

なお、数値オブジェクト2つの間に..を挟むと、Rangeクラスのオブジェクトになります。

{% highlight ruby linenos %}
(0..9).class
#=> Range
{% endhighlight %}

Rangeクラスのオブジェクトは、以下のように配列に変換して使われることが多いです。

{% highlight ruby linenos %}
list = (1..10).to_a # 1..10のRangeオブジェクトを、to_aメソッドで配列に変換
list.sample
#=> 1〜10の値がランダムに表示される
{% endhighlight %}


### メソッドの定義

C言語で自分の関数が作ることができたように、Rubyでも自分のメソッドを定義することができます。

名前を引数として受取り、「Hello, Takuya!」というように表示する hello メソッドは、以下のように定義できます。

{% highlight ruby linenos %}
def hello(name)
  puts "Hello, #{name}!"
end

hello("タクヤ")
#=> Hello, タクヤ!
{% endhighlight %}

また、テキストと飾り用の記号を受取り、飾り付けをしたテキストを返す decorate メソッドは、以下のように定義できます。

{% highlight ruby linenos %}
def decorate(text, mark)
  mark + text + mark
end

text = "こんにちは"
mark = "！！！"
decorated_text = decorate(text, mark)
puts decorated_text
#=> ！！！こんにちは！！！
{% endhighlight %}

C言語では、関数の引数や返り値の型の宣言が必要でしたが、Rubyでは必要ありません。また、return文もRubyでは省略することができます。return文を省略した場合は、最後に評価された式の結果がメソッドの返り値として返されます。


## 練習問題

### 1. 女性と子供の安心車両判定プログラム

以下の条件をみたすときに、「女性と子供の安心車両に乗ることができます。」と表示するプログラムを作成してください。ファイル名は sapporo.rb とします。

- 女性（genderが'f'の時）
- 12歳以下

なお、キーボードからの入力は以下のようにして受け取ることができます。

{% highlight ruby linenos %}
input = gets() # キーボードから入力
input.chomp!    # input変数の最後の1文字を削除する（変数inputには改行コードが含まれているため）
{% endhighlight %}


### 2. パスワード生成器

パスワードを生成するメソッド gen_password を定義し、それを使用してパスワードを出力するプログラムを作成してください。

仕様は以下の通りとします。

- 引数として文字数を受取り、受け取った文字数分のパスワードを出力すること。
- パスワードの範囲は、アルファベット大文字と小文字のみとする。

なお、配列オブジェクトのsampleメソッドは、以下のように数値を引数として取り、その数だけランダムに要素を出力するという事ができます。

{% highlight ruby linenos %}
list = ['T', 'A', 'K', 'U', 'Y', 'A']
list.sample(3) # ランダムに3つ取り出す
#=> ["K", "A", "Y"]
{% endhighlight %}


### 3. ソースコードに行番号自動でつけるマシーン

ソースコードのファイルを読み込み、先頭に行番号をつけて出力するプログラムを作成してください。

動作例は以下のとおりです。

![ソースコードに行番号自動でつけるマシーンの動作例]({{ site.baseurl }}/images/add_line_numbers_example.png)

Rubyでファイルを読み込むには、以下のようなコードを書きます。

{% highlight ruby linenos %}
# 1行ずつ読み込む
File.open('hello.c') do |file|
  file.each do |line|
    puts line
  end
end
# line変数に、1行ずつファイルの中身が格納されている。
{% endhighlight %}

