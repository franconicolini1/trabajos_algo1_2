import React from 'react'
import {
	BrowserRouter as Router,
	Switch,
	Route
} from 'react-router-dom'
import Menu from './components/Menu'
import Login from './components/Login'
import Admin from './components/Admin'
import Home from './components/Home'

function App() {
	return (
		<Router>
			<Menu></Menu>
			<Switch>
				<Route exact path='/' component={Home}></Route>
				<Route path='/admin' component={Admin}></Route>
				<Route path='/login' component={Login}></Route>
			</Switch>
		</Router>
	)
}

export default App