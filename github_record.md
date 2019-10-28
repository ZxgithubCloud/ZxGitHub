


### HEAD detached from resolve method
- git reflog 找到需要恢复的commit ，记下前面的commit id
- git branch temp efa64f5 新建一个名字叫temp的分支，用这个分支代替之前的临时分支并且拥有想要恢复的commit，efa64f5为要恢复的commit id
- git push origin temp推送到仓库
- git checkout master切换到主分支
- git merge temp 将temp合并到master
- 保险起见，先git push origin master 推送到仓库
- 查看是否更新，若更新则git branch -D temp删除该分支

#### Head detach resolve link
- [Head detach resolve](https://blog.csdn.net/u011240877/article/details/76273335)


### 
