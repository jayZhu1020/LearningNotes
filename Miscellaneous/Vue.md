# VUE
## `vue.js`
Vue is based on the idea of virtual DOM. A DOM (Document Object Model) is used as the structure of the HTML files where components are nested within each other. To search a component in a DOM, the cost is expensive. Virtual DOM represents each DOM component as a Javascript Object, and we can dynamically modifies its property to reflect that in the actual DOM in HTML.

Vue can be added as an instance to a webpage and all of its resources reside within that object. The `Vue()` constructor takes in a JS object with some properties
```javascript
var vm = new Vue({
  // options
})
```
The key properties are 
1. `el`: When a Vue instance is created, it looks for an element in the webpage to control. That element will be defined by the developer. It can be defined by assigning that element (usually a `div`) an `id`. This `id` is then mentioned in the Vue instance as the value of the `el` key.
2. `template`: The `template` defines what the Vue instance would display. The template is an HTML style element that can be controlled by the Vue instance. This actually replaces the element in the HTML file whose `id` is mentioned in the Vue instance.
3. `data`: The `data` is the store of a Vue instance. It stores all the variables it needs.
4. `methods`: A Vue instance may also need to perform some tasks. For this, it can also have its own methods or functions that can be defined in the methods key of the Vue instance.
Example:
```javascript
new Vue({
  el: '#app',
  template:
  `<div>
    <h1>Vue.js Application</h1>
    <p> {{name}}'s age is {{age}}</p>
    <button @click="incrementAge">Increment Age</button>
  </div>
  `,
  data: {
      name: 'John',
      age: 26
  },
  methods: {
      incrementAge() {
            this.age++
      }
  }
})
```
Also vue needs ti be imported using `<script src="https://cdn.jsdelivr.net/npm/vue@2"></script>`

## Mount Vue.js
Two ways to mount vue virtual DOM to the HTML:
1. Use `el=#app`. This mounts the content right away
```javascript
<!-- This is the div that is assigned the id= 'app' -->
<div id='app'></div>

<script>
new Vue({
    el: '#app' , // This is a way to mount Vue instance!
    ...
})
</script>
```
2. Use `$mount('#app')` on the Vue instance. This allows aynchronous mounting.
```javascript
<!-- This is the div that is assigned the id= 'app' -->
<div id='app'></div>

<script>
new Vue({
    ...
}).$mount('#app') //This is another way to mount Vue instance!
</script>
```

## Data and function in vue
The data property in a Vue instance is responsible for storing the variables for that particular instance. The accepted types are:
* String - Stores strings
* Number - Stores integers, floating point, and exponential notations
* Boolean - Stores ‘true’ or ‘false’
* Null - Represents null value
* Object - Stores a dictionary
* Array - Stores a list of variables
Variables are reference in the template using `{{}}`. For example, the following template renders the name in template with `{{name}}`
```javascript
new Vue({
  el: '#app',
  template:
  `<div>
    <h1> Vue.js Application </h1>
    <p> My name is {{name}}. See how my name is referenced from the data!</p>
  </div>
  `,
  data: {
      name: 'John'
  }
})
```

We can also call the function using `{{functionname()}}` inside template string. We can also access data in the function using `this`
```javascript
new Vue({
  el: '#app',
  template:
  `<div>
    <h1> Vue.js Application </h1>
    <p> My name is {{getMyName()}}. See how my name is retrived using a function!</p>
  </div>
  `,
  data: {
      name: 'John'
  },
  methods: {
    getMyName: function(){
      return this.name;
    }
  }
})
```

## Vue lifecycle
Every vue instance has 4 phases: 
1. create
2. mount
3. update
4. destory

And there are methods called lifecycle hooks that can perform certain tasks during those stages:
1. Creation hooks
`beforeCreate`
`created`
2. Mounting hooks
`beforeMount`
`mounted`
3. Updating hooks
`beforeUpdate`
`updated`
4. Destruction hooks
`beforeDestroy`
`destroyed`

```javascript
let myVM = new Vue({
  el: '#app',
  template:
  `<div>
    <h1>Vue.js Application</h1>
    <p> Please see the console below to view when each lifecycle hook is executed!</p>
    <h3> The instance will be destroyed after three seconds! So, destruction hooks will run later. </h3>
  </div>
  `,
  beforeCreate() {
    console.log('Events and lifecycle have been initialized');
  },
  created() {
    console.log('Vue instance have been created!');
  },
  beforeMount() {
    console.log('vm.$el has not been created yet.')
  },
  mounted() {
    console.log('vm.$el has been created and el has been replaced.')
  },
  beforeUpdate() {
    console.log('Virtual DOM has not re-rendered or patched yet');
  },
  updated() {
    console.log('Virtual DOM has re-rendered and patched.');
  },
  beforeDestroy() {
    console.log('Destroyed!!! Watchers and event listeners have not been teared down yet.');
  },
  destroyed() {
    console.log('Watchers and event listeners have been torn down');
  }
});

setTimeout(function() {
	myVM.$destroy();
}, 3000);
// Events and lifecycle have been initialized
// Vue instance have been created!
// vm.$el has not been created yet.
// vm.$el has been created and el has been replaced. 
// ... 3 SECONDS LATER ...
// Destroyed!!! Watchers and event listeners have not been teared down yet.
// Watchers and event listeners have been torn down
```

## Directives
Directive is a special token that tells Vue what to do with a certain DOM element. The syntax is:
```javascript
<element
  prefix-directiveId="[argument:] expression [| filters...]">
</element>
```
Note that it contains 5 parts:
1. prefix
2. directiveId
3. arguments
4. expressions
5. filters

