# HiveWE
HiveWE 是一款魔兽争霸 III 世界编辑器（WE），专注于速度与易用性。
相较于原版 WE 有显著提升，尤其是在大地图上，原版世界编辑器常常过慢且笨重。
目标是成为一款轻量工具，只做必须的事情，把其他任务交给高质量的外部应用。

## 本仓库目标
- 中文支持
- 兼容 Warcraft III 1.27 版本

[Hiveworkshop 论坛帖](https://www.hiveworkshop.com/threads/introducing-hivewe.303183/)

相较于原版 WE 的优势：
- 更快的加载
- 更快的渲染
- 更快的编辑
- 现代化 UI/UX
- 直接编辑路径贴图
- 编辑全局地形行走性
- 导入高度图
- 改进的编辑面板

## 功能

- 地形编辑
![HiveWE 截图](/Screenshots/HiveWE.png)
- 高级物体编辑器
![HiveWE 截图](/Screenshots/ObjectEditor.png)
- 直接编辑路径贴图  
![编辑路径贴图](/Screenshots/PathingEditing.png)
- 编辑全局地形行走性  
![编辑全局地形行走性](/Screenshots/GlobalPathingEditing.png)

## 下载

二进制下载请参见 [releases 页面](https://github.com/stijnherfst/HiveWE/releases)。

## 其他社区工具

触发器编辑：[WC3 Typescript](https://cipherxof.github.io/w3ts/)  
模型编辑：[3DS Max 插件](https://github.com/TaylorMouse/warcraft_III_reforged_tools)
或 [Retera Model Studio](https://github.com/Retera/ReterasModelStudio)

## 构建说明

0. 需要 Visual Studio 17.14 或更高版本（C++20 模块）
1. 将 HiveWE 克隆到本地任意目录  
`git clone https://github.com/stijnherfst/HiveWE.git`
2. 将 [vcpkg](https://github.com/microsoft/vcpkg) 克隆到一个统一目录（例如 "C:/")  
`git clone https://github.com/Microsoft/vcpkg.git`
3. 运行 `vcpkg/bootstrap-vcpkg.bat`
4. 在系统中添加一个用户环境变量：  
- `VCPKG_ROOT`：vcpkg 的安装位置（例如 "C:\vcpkg"）
5. 以**管理员**身份打开 Visual Studio，并使用“打开文件夹”按钮打开 HiveWE 目录。（Windows 下创建符号链接需要**管理员权限**）
6. 依赖会自动编译，可能需要 15-20 分钟（主要由于 Qt）

**完成**

如果遇到问题，欢迎在 HiveWorkshop 联系我（eejin），或在 Discord 上联系 eejin#4240。

## 潜在贡献

想参与 HiveWE 的开发？以下是一些可以实现的功能。你可以尝试其中之一，或添加你认为 HiveWE 需要的其他内容。欢迎任何贡献！

- 能够修改势力/队伍
- 修改地图尺寸/镜头范围
- 使用地形面板编辑斜坡
- 让 HiveWE 更快
- FDF 框架编辑器
- 文本着色器
- 高级地形编辑工具（例如洪泛填充、魔棒选择）
- 或其他你认为很酷的功能

如果你有任何问题，欢迎在这里、HiveWorkshop（eejin）或 Discord（eejin）联系我。
