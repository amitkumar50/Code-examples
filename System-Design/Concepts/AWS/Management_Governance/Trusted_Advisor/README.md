**Trusted Advisor**
- [Advise Examples](#ae)

## Trusted Advisor
Web service which inspects AWS env and provide best practices recommendations in 5 categories: 
- Cost optimization, Performance, Security, Fault tolerance, Service limits
<img src=trusted-advisor.JPG width=500 />

<a name=ae></a>
### Advise Examples
- **MFA** is not enabled OR
- **EC2 instances** 
  - under utilized OR
  - ports that allow unrestricted access. TA scans Security groups on EC2 instance.
- **EBS volumes** those are not backed up in reasonable amount of time.  
- **S3 bucket** permissions in Amazon S3 with open access permissions.
- Recommendation can be:
  - Warning, Alert, Nothing
