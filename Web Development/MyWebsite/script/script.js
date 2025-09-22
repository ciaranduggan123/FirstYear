function messageOutput(){
  const name = document.getElementById('userName').value;
  document.getElementById("message").textContent = "Welcome to the website, " + name;
}

const listWhite = document.getElementsByClassName("white");

function modifyColour(){
	for (let i =0; i<listWhite.length; i++){
  listWhite[i].style.backgroundColor="#000080";
  }
}

//this function will change the text of an element to "New stuff"
function changeFirst() {
  document.querySelector(".example").textContent = "Sigurdson Cup Team";
}

//this function will change the text of all elements to "More new stuff"
function changeAll(){
	const selectAll = document.querySelectorAll(".example");
	for	(i = 0; i < selectAll.length; i++){
		let item = selectAll[i];
    item.textContent = "Last Game v UL: TUD 2-8 Ul 3-14";
    item.textContent = "Next game is against Mary I on 18th of December"
	}
}

const name = ["John", "Mary", "Anne", "Joseph", "Kate"];
document.getElementById("clientName").innerHTML = name[0];

// Array of Irish counties
const irishCounties = [
  'Antrim', 'Armagh', 'Carlow', 'Cavan', 'Clare', 'Cork', 'Derry', 'Donegal',
  'Down', 'Dublin', 'Fermanagh', 'Galway', 'Kerry', 'Kildare', 'Kilkenny',
  'Laois', 'Leitrim', 'Limerick', 'Longford', 'Louth', 'Mayo', 'Meath',
  'Monaghan', 'Offaly', 'Roscommon', 'Sligo', 'Tipperary', 'Tyrone',
  'Waterford', 'Westmeath', 'Wexford', 'Wicklow'
];

// Function to display Irish counties on the webpage
function displayCounties() {
  const countyList = document.getElementById('county-list');

  irishCounties.forEach(county => {
    // Create a new list item element
    const listItem = document.createElement('li');
    
    // Set the text content of the list item
    listItem.textContent = county;

    // Append the list item to the unordered list
    countyList.appendChild(listItem);
  });
}

// Call the function to display Irish counties
displayCounties();


// Define a customer object
let player = {
  id: 1,
  name: "John Doe",
  email: "john.doe@example.com",
  address: {
      street: "123 Main St",
      city: "Anytown",
      province: "Leinster",
      eircode: "12345"
  },
  orders: [
      { id: 101, product: "Laptop", price: 999.99 },
      { id: 102, product: "Smartphone", price: 499.99 },
      // ... more orders
  ]
};

// Accessing and updating customer information
console.log(player.name); // Output: "John Doe"
console.log(player.address.city); // Output: "Anytown"

// Adding a new order
const newOrder = { id: 103, product: "Tablet", price: 299.99 };
//push method is used to add a new element
player.orders.push(newOrder);

// Displaying the updated customer object
console.log(player);

// Example object representing an Irish county
const irishCounty = {
  name: 'Dublin',
  province: 'Leinster',
  population: 544107
};

// Function to display county information on the webpage
function displayCountyInfo() {
//Select the div with id county-info
  const countyInfoContainer = document.getElementById('county-info');
  // Display the county object properties on the webpage
  countyInfoContainer.innerHTML = `
    <p>Name: ${irishCounty.name}</p>
    <p>Province: ${irishCounty.province}</p>
    <p>Population: ${irishCounty.population}</p>
  `;
}

// Call the function to display county information
displayCountyInfo();

function validateForm() {
  var name = document.getElementById('name').value;
  var email = document.getElementById('email').value;
  var message = document.getElementById('message').value;

  // Simple check for empty fields
  if (name.trim() === '' || email.trim() === '' || message.trim() === '') {
      alert('All fields must be filled out');
      return false;
  }

  // Check for a valid email format
  var emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  if (!emailRegex.test(email)) {
      alert('Please enter a valid email address');
      return false;
  }

  // If everything is valid, the form will be submitted
  return true;
}

