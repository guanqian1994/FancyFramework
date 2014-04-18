FancyFramework
==============

FancyFrameworks是基于Fancy2D的一个轻量级框架，它可以让你方便地创建图形应用程序。

你必须使用 VS2013 打开这个项目.

* 前往 [Fancy2D](https://github.com/9chu/fancy2d)

创建第一个应用程序
==============

在创建第一个应用程序之前，你先得配置好 FancyFramework 和 Fancy2D 以及其他依赖项目的头文件和链接库。

最简单的 FancyFramework 程序由一个类完成：
```code
class FirstApp : public ffAppEventListener {
public:
    FirstApp() {
        ffApp::Run(this, 800, 600, L"App");
    }
};
int main() {
    FirstApp app;
}
```

编译，运行，可以看到一个黑色的窗口。

ffApp::Run 方法是整个框架的入口，可以指定窗口尺寸、是否全屏、标题、垂直同步和抗锯齿模式。但必须指定一个有效的 ffAppEventListener 类型对象，用于监听框架必须处理的事件。这里通过继承它来获得处理事件的功能，用户代码中可以不实现所不需要的框架事件，它们已经有了默认的实现。

更多参考示例代码。

便捷加载资源
==============
经过封装的资源系统以便更加轻易的加载资源且保持原有f2d对象操作。

```code
ffSprite::Ref pSprite = ffSprite::Create(L"Res\\image.png");
pSprite->Draw(...);
```

贴图和音频类型的资源底层会维护同一个原始对象，例如从某资源位置加载多次贴图精灵，实际都是使用的同一个贴图对象，不会加载多次贴图对象。

增加贴图集类 ffImageset 和 贴图动画类 ffAnimation，你可以通过工具来生成所需的资源类型[ImagesetEditor](https://github.com/frimin/ImagesetEditor)

模块
==============
* FancyFramework : 基础框架
* FancyFrameworkUI : UI扩展，提供简单的UI功能
