## std::thread vs std::thread

||std::thread|std::future, std::promise or std::async|
|---|---|---|
|What|Seperate execution|<ul><li>Operate on threads, data can be transferred without locks</li></ul><ul><li>When a task wants to pass a value to another, it puts the value into a promise</li></ul><ul><li>When want to retrieve value get it in future</li></ul>|
