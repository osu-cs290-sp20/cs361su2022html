# cs361su2022

This program currently needs to be run locally with flask, but will be hosted online soon.
To request data from the program, run the program and go to http://127.0.0.1:5000/api/resumes?id=0
The id variable can be changed to reflect the id of a resume that has been entered, but as default there are no resumes in the program and id=0 is essentially a blank page.

Data is returned in a json package like so:
{
  "id": 1,
  "percent": 85.2
}

To send data to the program, send as a json packet to http://127.0.0.1:5000/api/resumes when running this on your machine. 
This data will be processed when a request is sent with the id of the resume.


An easy way to send data in the command line is to type what is below and fill in information for "id", "resume" and "job.

curl -i http://127.0.0.1:5000/api/resumes -X POST -H 'Content-Type: application/json' -d '{"id":, "resume":"", "job":""}'

[UML.pdf](https://github.com/solom69685/cs361su2022/files/9205125/UML.pdf)
