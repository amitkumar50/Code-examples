## Issues

|Issue|Steps|
|---|---|
|1. git clone remote head refers to nonexistent ref|<ul><li>Head(.git/HEAD) is a file storing reference to checkout branch</li></ul> <ul><li>ref: ref is a file storing hash of recent commit on checkout branch</li></ul> <ul><li>This error means:HEAD exists, but ref(File storing SHA-1 of recent commit on remote branch) is missing</li></ul> <ul><li>To resolve the issue(Admin can create symbolic links)# cd path/to/repo; git symbolic-ref HEAD refs/heads/master</li></ul>|

### Issue-1 (remote head refers to nonexistent ref)
```
# git checkout test-repo
test-repo$ git branch
  * master
test-repo$ cat .git/HEAD                    <<HEAD exist
  ref: refs/heads/master
test-repo$ cat .git/refs/heads/master       <<ref does not exist
  257143e8aded4f0fca7712105581567162cab60c
test-repo$
```
