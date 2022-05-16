import React, { useEffect, useState } from 'react'
import { db } from './firebaseConfig'

function App() {
	const [name, setName] = useState('')
	const [phone, setPhone] = useState('')
	const [error, setError] = useState('')
	const [users, setUsers] = useState([])
	const [updateId, setUpdateId] = useState('')

	const getUsers = async () => {
		const { docs } = await db.collection('users').get()
		const res = docs.map(item => ({id: item.id, ...item.data()}))
		setUsers(res)
	}

	useEffect(() => {
		const getUsersAux = async () => {
			const { docs } = await db.collection('users').get()
			const res = docs.map(item => ({id: item.id, ...item.data()}))
			setUsers(res)
		}
		getUsersAux()
	}, [])	

	const createUser = async (e) => {
		e.preventDefault()
		if (isNaN(parseInt(phone))) return setError('El teléfono debe ser un número')
		if (!name.trim() || !phone.trim()) return setError('Ambos campos deben estar completos')
		
		const user = {
			name,
			phone
		}
		
		try {
			await db.collection('users').add(user)
			getUsers()
			setName('')
			setPhone('')
			setError('')
		} catch(e) {
			console.log(e)
		}
	}

	const deleteUser = async (id) => {
		await db.collection('users').doc(id).delete()
		getUsers()
	}

	const userMode = async (id) => {
		try {
			const info = await db.collection('users').doc(id).get()
			const { name, phone } = info.data()
			setName(name)
			setPhone(phone)
			setUpdateId(id)

		} catch(error) {
			console.log(error)
		}
	}

	const cancelUserMode = () => {
		setUpdateId('')
		setName('')
		setPhone('')
	}

	const updateUser = async (e) => {
		e.preventDefault()
		if (isNaN(parseInt(phone))) return setError('El teléfono debe ser un número')
		if (!name.trim() || !phone.trim()) return setError('Ambos campos deben estar completos')
		
		const userUpdate = {
			name,
			phone
		}

		try {
			await db.collection('users').doc(updateId).set(userUpdate)
			getUsers()
			setName('')
			setPhone('')
			setError('')
			setUpdateId('')
		} catch(e) {
			console.log(e)
		}
	}

	return (
		<div className='container'>
			<div className="row">
				<div className='col'>
					<h2>Formulario de Usuarios</h2>
					<form className='form-group' onSubmit={(e) => updateId ? updateUser(e) : createUser(e)}>
						<input 
							onChange={e => setName(e.target.value)}
							className='form-control mt-4'
							placeholder='Introduzca un nombre'
							type='text'
							value={ name }
						/>
						<input 
							onChange={e => setPhone(e.target.value)}
							className='form-control mt-3'
							placeholder='Introduzca un teléfono'
							type='tel'
							value={ phone }
						/>
						<input
							className='btn btn-block btn-dark mt-4 w-100'
							value={ updateId ? 'Actualizar Usuario' : 'Registrar' }
							type='submit'
						/>
						{
							error ?
							<p className='text-danger mt-2'>{ error }</p>
							:
							<span></span>
						}
					</form>
				</div>
				<div className='col ms-5'>
					<h2>Lista de tu Agenda</h2>
					<ul className="list-group mt-4">
						{
							users.length ? 
								(
									users.map(item => (
										<li className='list-group-item' key={ item.id }>
											{ item.name } - { item.phone }
											<button 
												className='btn btn-danger float-end'
												onClick={() => deleteUser(item.id)}
											>Borrar</button>
											<button 
												className='btn btn-primary float-end me-2'
												onClick={() => userMode(item.id)}
											>Actualizar</button>
											{
												updateId && updateId === item.id ?
												<button 
													className='btn btn-secondary float-end me-2'
													onClick={() => cancelUserMode()}
												>Cancelar</button>
												:
												<span></span>
											}
										</li>
									))
								)
							:
							<li className='list-group-item'>No hay usuarios en tu agenda</li>
						}
					</ul>
				</div>
			</div>
		</div>
	)
}

export default App