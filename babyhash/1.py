import hashlib
for a1 in range(97,123):
    print(a1)
    for a2 in range(97,123):
        for a3 in range(97,123):
            for a4 in range(97,123):
                for a5 in range(97,123):
                    for a6 in range(97,123):
                        key=''
                        key='12345'+chr(a1)+chr(a2)+chr(a3)+chr(a4)+chr(a5)+chr(a6)+'67890'
                        key_md5 = hashlib.md5(key.encode(encoding='utf-8')).hexdigest()
                        if(key_md5=='f27d71f53ae17679fb352baa5ea326db'):
                          print(key)
