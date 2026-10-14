# Aura

基于 Unreal Engine 5.6 的 Gameplay Ability System（GAS）学习项目。

## 打开项目

1. 克隆本仓库，安装 Unreal Engine 5.6 和支持 UE C++ 开发的编译工具。
2. 如果本机无法识别 `Aura.uproject` 的引擎关联，右键该文件，选择“切换 Unreal Engine 版本”，指定本机的 UE 5.6。
3. 右键 `Aura.uproject`，生成项目文件，编译 `AuraEditor`，然后打开项目。
4. 默认地图为 `Content/Maps/StartupMap.umap`。

## 仓库内容

- `Source/`：C++ 源码和构建定义。
- `Config/`：项目设置。
- `Content/BluePrint/`、`Content/Maps/`：项目自己的蓝图和地图。
- `Content/Assets/`：当前蓝图和地图实际引用的模板角色、动画、材质、声音及 UI 素材。
- `Platforms/`：平台配置。

编译产物、着色器缓存、日志、自动保存和个人 IDE 设置通过 `.gitignore` 排除，可在本机重新生成。

本仓库采用精简素材范围，约 266 MiB，不包含完整模板素材包。未使用的大型场景和其他角色等素材保留在原本机目录，通过 `.gitignore` 中的素材白名单排除上传。后续需要上传新的模板素材时，应同步更新白名单，并包含该素材引用的依赖。
