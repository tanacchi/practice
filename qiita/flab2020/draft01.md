【C++】最もわかりやすいダブルディスパッチの解説

**初カキコ…ども…**  
タイトルは釣りなので気にしないでください。

# はじめに
もともと  
**「C++の入出力演算子にポリモーフィックな挙動をさせたい」**  
っていうタイトルにするつもりでした。  
一体誰が読むんだ…と思って~~バズりそうなやつに~~変えた次第です。  

もちろん入出力演算子（`<<`とか`>>`）だけでなく、あらゆる関数のデザインで応用できるテクニックです。

# ポリモーフィズムとは(C++編)
知ってるよって人は本題まで読み飛ばしてください。

例えば、動物(Animal)クラスから犬(Dog)クラスと猫(Cat)クラスが継承している状況があるとします。
動物たちはそれぞれ `void introduce()` という関数を持っていて、これを呼ぶと自己紹介してくれます。

```C++:poly1.cpp
#include <iostream>

class Animal
{
  public:
    Animal(std::string name)
      : name_{name}
    {
    }

    void introduce()
    {
      std::cout << name_ << "だよ !! ";
    }

  private:
    std::string name_;
};


class Dog : public Animal
{
  public:
    Dog(std::string name)
      : Animal(name)
    {
    }

    void introduce()
    {
      Animal::introduce();  // 基底クラスの introduce関数を呼ぶ
      std::cout << "わんわんお !!!" << std::endl;
    }
};

class Cat : public Animal
{
  public:
    Cat(std::string name)
      : Animal(name)
    {
    }

    void introduce()
    {
      Animal::introduce();  // 基底クラスの introduce関数を呼ぶ
      std::cout << "お゛お゛ん !!!" << std::endl;
    }
};

int main()
{
  Dog dog{"ポチ"};
  Cat cat{"たま"};

  dog.introduce();  // ポチだよ !! わんわんお !!!
  cat.introduce();  // たまだよ !! お゛お゛ん !!!

  return 0;
}
```

同じ `void introduce()` 関数を呼んでいますが、それぞれ異なった挙動をしてくれます。
当然です。

さて、これにポリモーフィックな挙動をしてもらうために、`void Animal::introduce()` を仮想関数に変更します。

すると、次のようなことが出来ます。

```C++:poly2.cpp
#include <iostream>

class Animal
{
  public:
    Animal(std::string name)
      : name_{name}
    {
    }

    virtual void introduce()  // 仮想関数化！！！
    {
      std::cout << name_ << "だよ !! ";
    }

  private:
    std::string name_;
};

class Dog : public Animal
{
  public:
    Dog(std::string name)
      : Animal(name)
    {
    }

    void introduce() override
    {
      Animal::introduce();  // 基底クラスの introduce関数を呼ぶ
      std::cout << "わんわんお !!!" << std::endl;
    }
};

class Cat : public Animal
{
  public:
    Cat(std::string name)
      : Animal(name)
    {
    }

    void introduce() override
    {
      Animal::introduce();  // 基底クラスの introduce関数を呼ぶ
      std::cout << "お゛お゛ん !!!" << std::endl;
    }
};

int main()
{
  Animal* dog_ptr{new Dog("ポチ")};  // 簡単のため生ポインタ& new 演算子
  Animal* cat_ptr{new Cat("たま")};

  dog_ptr->introduce();  // ポチだよ !! わんわんお !!!
  cat_ptr->introduce();  // たまだよ !! お゛お゛ん !!!

  return 0;
}
```

`dog_ptr` も `cat_ptr` も、同じ Animalクラスのポインタです。
それぞれが Dog, Cat のインスタンスを指している状況になっています。
`void introduce()` の呼び出し時に、ポインタが指している実態が何なのかを実行時に判別して
勝手に関数の挙動を変えてくれています。
これがポリモーフィズム(polymorphism)です。(超簡易版)

少し調べるとポリモーフィズムにも種類があるようで、
今回取り扱うのは「サブタイピング多相」というものらしいです。
ふーんって感じです。

使いみちの例
ボードゲームを作成するときに
人間vs人間 と 人間vsコンピュータ を(コマンドライン引数などで)実行時に設定できるようにしたいとします。
そういう時に player2 が人間かコンピュータかでいちいち分岐するのではなく、
ポリモーフィックな設計をすることでスマートに書くことが出来ます。

```C++:poly_example.cpp
#include <iostream>
#include <utility>

using Point = std::pair<int, int>;

class Player
{
  public:
    virtual Point get_hand() = 0;
};

class HumanPlayer: public Player
{
  public:
    Point get_hand()
    {
      // 標準入力やらで人間に次の手を入力させる
    }
};

class ComputerPlayer : public Player
{
  public:
    Point get_hand()
    {
      // 計算やら乱数やらで次の手を決定する
    }
};

int main()
{
  Player* player1_ptr{new HumanPlayer()};
  Player* player2_ptr{new ComputerPlayer()};

  Point point;

  point = player1_ptr->get_hand();  // HumanPlayer の挙動をする
  point = player2_ptr->get_hand();  // ComputerPlayer の挙動をする

  return 0;
}
```

`player2_ptr` の中身を `HumanPlayer` にするか `ComputerPlayer` にするかを
コマンドライン引数などで分岐できるようにしてしまえばめでたし。

# 本題

今度はメンバ関数ではなく出力ストリーム用のグローバルな関数を作ります。
とりあえず書いてみたのがこんな感じ。

```C++:single_dispatch.cpp
#include <iostream>

class Animal
{
  public:
    Animal(std::string name)
      : name_{name}
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Animal& animal)
    {
      os << animal.name_ << "だよ !!! ";
      return os;
    }

  protected:  // Dog, Cat からのアクセス権が必要なので private にはできない
    const std::string name_;
};

class Dog : public Animal
{
  public:
    Dog(std::string name)
      : Animal(name)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Dog& dog)
    {
      os << dog.name_ << "だよ !!! わんわんお !!!";
      return os;
    }
};

class Cat : public Animal
{
  public:
    Cat(std::string name)
      : Animal(name)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Cat& cat)
    {
      os << cat.name_ << "だよ !!! お゛お゛ん !!!";
      return os;
    }
};

int main()
{
  Dog dog{"ポチ"};
  Cat cat{"たま"};

  std::cout << dog << std::endl;  // ポチだよ !!! わんわんお !!!
  std::cout << cat << std::endl;  // たまだよ !!! お゛お゛ん !!!

  return 0;
}
```

この関数はグローバルなので、「親の関数」を呼ぶことができないのでスマートではありません。
さらに Dog, Cat も Animal::name を参照しなくちゃいけないので
name を private: 属性にすることも出来ません
~~クソクソのクソです。~~

さらにポリモーフィックな挙動をさせようとすると、、

```C++
int main()
{
  Animal* dog_ptr{new Dog("ポチ")};
  Animal* cat_ptr{new Cat("たま")};

  std::cout << *dog_ptr << std::endl;  // ポチだよ !!!
  std::cout << *cat_ptr << std::endl;  // たまだよ !!!

  return 0;
}
```

おや、基底クラス(Animal)の方が呼ばれてますね・・・
引数部分では実態が何なのか判別できないのかな
困ったことになりました。

# 解決策
早い話、**ダブルディスパッチ** を使えば解決します。  

先ほどの出力処理を `std::string to_string()` という別の関数に移動させます。
次に、出力演算子の内部で `std::string to_string()` を呼ぶようにします。

```C++:double_dispatch.cpp
#include <iostream>
#include <sstream>

class Animal
{
  public:
    Animal(std::string name)
      : name_{name}
    {
    }

    virtual std::string to_string() const
    {
      std::stringstream ss;
      ss << name_ << "だよ !!! ";
      return ss.str();
    }

  private:
    const std::string name_;
};

class Dog : public Animal
{
  public:
    Dog(std::string name)
      : Animal(name)
    {
    }

    std::string to_string() const override
    {
      std::stringstream ss;
      ss << Animal::to_string() << "わんわんお !!!";
      return ss.str();
    }
};

class Cat : public Animal
{
  public:
    Cat(std::string name)
      : Animal(name)
    {
    }

    std::string to_string() const override
    {
      std::stringstream ss;
      ss << Animal::to_string() << "お゛お゛ん !!!";
      return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Animal& animal)
{
  os << animal.to_string();
  return os;
}

int main()
{
  Animal* dog_ptr{new Dog("ポチ")};
  Animal* cat_ptr{new Cat("たま")};

  std::cout << *dog_ptr << std::endl;  // ポチだよ !!! わんわんお !!!
  std::cout << *cat_ptr << std::endl;  // たまだよ !!! お゛お゛ん !!!

  return 0;
}
```

`animal.to_string()` のように呼びだせば ポリモーフィズムとはの項目の `void introduce()` 関数と何も変わらないわけです。

# 要するに
実体が何者なのかは、

**引数部分で判別することはできない。**  
**実際にそれを触って・動かして初めて実体が何なのかが分かる。**  

ダブルディスパッチとは、この考えのもとにあるのではないでしょうか。  
え、知ってた？


# おわりに
趣味で[RPGゲーム](https://github.com/tanacchi/rogue_game)を作ってて今回のテクニックが必要になりました。  
このテクニックにダブルディスパッチっていう名前がついてることを知ったのは  
実装からしばらく経ってからでした。  
世紀の大発見ならず。トホホ

# 余談
ダブルディスパッチを使わない方法は無いのかと、`type_traits` を使って頑張ってましたが
やっぱりダメでした
もし知っている方いましたら教えてください。
