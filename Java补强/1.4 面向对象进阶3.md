# 面向对象进阶

## 内部类
在Java程序中，通常情况下，我们把不同的类组织在不同的包下面，对于一个包下面的类来说，它们是在同一层次，没有父子关系  

还有一种类，它被定义在另一个类的内部，所以称为内部类Nested Class

### 内部类 Inner Class 
如果一个类定义在另一个类的内部，这个类就是Inner Class   
```Java
class Outer{
    class Inner{

    }
}
```

内部类的特点在于，Inner Class的实例不能单独存在，必须依附于一个Outer Class的实例    
```Java
public class Main {
    public static void main(String[] args) {
        Outer outer = new Outer("Nested"); // 实例化一个Outer
        Outer.Inner inner = outer.new Inner(); // 实例化一个Inner
        inner.hello();
    }
}

class Outer {
    private String name;

    Outer(String name) {
        this.name = name;
    }

    class Inner {
        void hello() {
            System.out.println("Hello, " + Outer.this.name);
        }
    }
}
```

显然，```Outer.Inner inner = outer.new Inner();```，我们要先创建一个Outer的实例，然后再调用Outer实例的```new```来创建Inner实例    

因为Inner Class除了有一个this指向它自己，还隐含地持有一个Outer Class实例，可以用Outer.this访问这个实例

> 实例化一个Inner Class不能脱离Outer实例

而Inner Class的特性还在于，它可以**修改Outer Class中的private字段的内容**   
> 因为Inner Class的作用域在Outer Class内部，所以能访问Outer Class的private字段和方法    

> 观察Java编译器编译后的.class文件可以发现，Outer类被编译为Outer.class，而Inner类被编译为Outer$Inner.class

### 匿名类 Anonymous Class  
