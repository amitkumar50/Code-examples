**WAF / Web Application Firewall**
- [WAF vs Sheild](#vs)

## WAF
- WAF (sort of wireshark+policy enforcer) that monitors network requests that come into your web applications and can block/allow traffic using WACL(web access control list)
- Example: Suppose your application has been receiving malicious network requests from several IP addresses.
  - You can apply WACL to block traffic from those IPs and keep allow rules from legitimate IPs.

<a name=vs></a>
### WAF vs Sheild

|Service|What|
|---|---|
|WAF|Firewall(protects against attacks)|
|Sheild|DDos Protection service|

