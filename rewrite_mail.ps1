git filter-repo --email-callback "
print(email)
if email == b'arnaud.dejarcy@gmail.com':
    #print('va rempl')
    return b'arnaud162@users.noreply.github.com'
    
return email" --force