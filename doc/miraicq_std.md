# MiraiCQ运作原理

[TOC]

## API规范

对于返回整数的api,若调用失败，返回负数。可能会有一定规律，但是**不要**过度依赖。

对于返回字符串的api,若调用失败，返回""，注意，永远不会返回空指针，所以，不必做多余的空指针判断。

对于返回字符串的API,字符串会在60秒后被释放，所以，必须在60秒内完成拷贝。

涉及的字符串，均为gbk编码

所以API均使用stdcall 导出，在CQP.dll中。

API列表可以参考相关的SDK:[API列表](https://github.com/howmanybots/cqcppsdk/blob/master/src/std_mode/api_funcs.inc)

## 事件规范

事件中的字符串，永远不会为空指针，所以，不必做多余的空指针判断。

事件中的字符串，会在事件函数结束后失效。

相同或者不同的事件函数，可能会在不同的线程调用，甚至不保证同一条消息在同一个线程中处理，所以，应该注意线程安全。

事件的返回值均无意义，这与酷Q有所不同，注意。

事件不存在优先级，这与酷Q有所不同，注意。

事件中的字符串，均为gbk编码。

## 事件调用顺序

Initialize（获取AC）

Initialize2 (拓展功能)

框架启动（type = 1001）

插件启用（type = 1003）

其他事件

插件停用（type = 1004）

框架退出（type = 1002）

以上事件中，除了Initialize，均为可选事件。

## 事件列表

### Initialize

原型：int32 stdcall Initialize(int32 authCode);

说明：通过这个事件获取authCode。这个事件会在插件加载时调用。在这个事件中还不能调用API，也不要再此处弹窗、阻塞。

参数：

authCode：调用API必备的参数

返回：无意义

### Initialize2

原型：int32 stdcall Initialize(void ** fp,int32 n);

说明： 此函数提供了一个使用onebot所有能力的方法(配合下面的1207号事件)，较为复杂，文档正在写。

返回：无意义

### 框架启动(type = 1001)

原型：int32 stdcall  user_name();

说明：这个事件会在框架启动时调用一次。在这个事件中，已经可以调用API了。不要再此处弹窗、阻塞。

返回：无意义

### 插件启用（type = 1003）

原型：int32 stdcall  user_name();

说明：这个事件会在插件启用时调用一次(插件总会在在框架启动后启用)。不要再此处弹窗、阻塞。

返回：无意义

### 私聊消息（type = 21）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 群消息（type = 2）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 群文件上传（type = 11）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 群管理员变动（type = 101）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 群成员减少（type = 102）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 群成员增加（type = 103）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 群禁言（type = 104）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

###  好友添加（type = 201）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

###  (拓展)群内戳一戳事件,user_id为发送者QQ（type = 202）

原型：__int32 event_notify_pock(__int64 group_id, __int64 user_id, __int64 target_id)

说明：略

参数：略

返回值：无意义

###  (拓展)群内运气王事件,user_id为发红包者QQ（type = 203）

原型：__int32 event_notify_lucky_king(__int64 group_id, __int64 user_id, __int64 target_id)

说明：略

参数：略

返回值：无意义

###  (拓展)群内荣誉变更事件,honor_type可以为talkative、performer、emotion（type = 204）

原型：__int32 event_notify_honor(__int64 group_id, const char * honor_type, __int64 user_id)

说明：略

参数：略

返回值：无意义

###  (拓展)群聊消息撤回事件,user_id为消息发送者QQ（type = 205）

原型：__int32 event_group_recall(__int64 group_id, __int64 user_id, __int64 operator_id,__int32 message_id)

说明：略

参数：略

返回值：无意义

###  (拓展)私聊消息撤回事件（type = 206）

原型：__int32 event_friend_recall(__int64 user_id, __int32 message_id)

说明：略

参数：略

返回值：无意义

###  (拓展)ws原始事件（type = 1207）

原型：__int32 user_name(const char * msg)

说明：此函数用于接收所有ws收到的所有事件。

参数msg：json字符串，编码为gbk

返回值：无意义

### 加好友请求（type = 301）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 加群请求／邀请（type = 302）

原型：与酷Q保持一致

说明：略

参数：与酷Q基本保持一致

返回值：无意义

### 插件停用(type = 1004)

原型：int32 stdcall  user_name();

说明：永不调用，占位

返回：无意义

### 框架退出（type = 1002）

原型：int32 stdcall  user_name();

说明：这个事件会在框架退出时调用一次。在这个事件中，可以调用API。不要再此处弹窗、阻塞。当这个事件被调用时，框架会在5秒内强制退出，请尽快做相应处理。

返回：无意义

## API列表

## json文件规范

json文件不支持注释

使用GBK编码（cp936）

json文件名除拓展名外，需要与dll名相同

一个简洁的json例子，包含所有有效的字段：

```json
{				
    "name":"私聊复读机",	
    "version":"1.0.0",							
    "author":"super",			
    "description":"这是一个私聊复读机插件。",
    "event":[					
        {				
            "type":21,								
            "function":"cq_private_msg"
        }
    ],
    "menu": [
        {
          "name": "检查更新",
          "function": "cq_menu_check_update"
        }
  	]
}
```

在json中，多余的字段将会被忽略。不需要的字段也可以不写。如：

```json
{				
    "name":"私聊复读机",	
    "version":"1.0.0",							
    "author":"super",			
    "description":"这是一个私聊复读机插件",
    "event":[					
        {				
            "type":21,								
            "function":"cq_private_msg",
            "priority": 20000
        }
    ]
}
```
