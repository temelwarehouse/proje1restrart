function submitForm(event) {
  event.preventDefault();
  // Get input field values
  const name = document.getElementById('name').value;
  const email = document.getElementById('email').value;
  const password = document.getElementById('password').value;
  const radioInputBuyer = document.getElementById("buyer_check");
  const radioInputSeller = document.getElementById("seller_check");

  let role = "";
  if (radioInputBuyer.checked) {
    role = "buyer";
  }else if (radioInputSeller.checked) {
    role = "seller";
  }
  // Create an object with the form data
  const formData = {
    name: name,
    email: email,
    password: password,
    role: role
  };

  // Send a POST request to your C++ backend
  fetch('http://localhost:8082/post', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(formData)
  })
    .then(response => {
      if (response.ok) {
        // Registration successful
        alert('Registration successful!');
      } else {
        // Registration failed
        alert('Registration failed.');
      }
    })
    .catch(error => {
      console.error('Error:', error);
    });
}