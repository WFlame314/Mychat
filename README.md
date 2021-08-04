#  软件说明

## 目录说明

##  各文件说明

##  使用说明

#  JSON说明

##  基本格式

```json
{
    // 类型:String 用于标识该JSON数据的功能。
	"type":"Type String",
	"data": {
				//内容
		    }
}
```

## 各功能格式

###  登录功能

#### 发送

``` json
{
	"type": "login",
    "data": {
        		// 类型:String 内容:登录账号。
                "account": "account string",
        		// 类型:String 内容:密码，或保存的密码密钥。
        		"password": "password or passwordkey", 
        		//类型:int 内容:登录方式(0:普通登录，1:passworkey登录)
        		"logintype": 0 || 1,
        		// 类型:int 内容:登录后的状态(0:离线，1:在线，2:隐身)。
        		"loginstate": 0 || 1 || 2,
        		// 类型:Bool 内容:辨识是否保存密码，若为true则服务器返回密码密钥。
        		"ifremember": true || false,
            }
}
```

####  接收

``` JSON
{
    "type": "login_return",
    "data": {
        		/* 
        		 * 类型: String 内容: 登录结果，
        		 * 密码错误："wrong_password"
        		 * 账号错误："wrong_account"
        		 * 登录成功："login_success"
        		 */
        		"state": "loginstate string";
    		}
}
```

