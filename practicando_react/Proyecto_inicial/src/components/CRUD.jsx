import React, { useState } from 'react'
import uniqid from 'uniqid'

const CRUD = () => {
    const [nameList, setNameList] = useState([])
    const [currentName, setCurrentName] = useState('')
    const [editMode, setEditMode] = useState(false)
    const [idToEdit, setIdToEdit] = useState('')

    const create = () => {
        if (currentName) {
            const newName = {
                id: uniqid(),
                name: currentName
            }

            setCurrentName('')
            setNameList([...nameList, newName])
        }
    }

    const Delete = (id) => {
        setNameList(nameList.filter(item => item.id !== id))
    }

    const edit = (obj) => {
        setEditMode(true)
        setIdToEdit(obj.id)
        setCurrentName(obj.name)
    }

    const editName = () => {
        if (currentName) {
            setNameList(nameList.filter(item => item.id === idToEdit ? item.name = currentName : item))
            setCurrentName('')
            setEditMode(false)
        }
    }

    return (
        <div className="container">
            <h1>Este es mi primer CRUD</h1>
            <div style={{marginBottom: 50}}>
                <h2>Esta es la lista:</h2>
                <ul>
                    {
                        nameList.map(obj => 
                            <div>
                                <li key={obj.id} style={{listStyle: 'none', marginTop: 8, display: 'inline-block'}}>{obj.name}</li>
                                <button onClick={() => edit(obj)}>EDITAR</button>
                                <button onClick={() => Delete(obj.id)}>BORRAR</button>
                            </div>
                        )
                    }
                </ul>
            </div>
            <div>
                <h2>Ingrese un nombre:</h2>
                <form onSubmit={e => e.preventDefault()}>
                    <input type="text" onChange={(e) => setCurrentName(e.target.value)} placeholder="Ingrese un nombre" value={currentName} style={{marginTop: 20, marginBottom: 20}}/><br/>
                    <input type="button" value={editMode ? "Editar Nombre" : "Registrar Nombre"} 
                        onClick={() => editMode ? editName() : create()}/>
                </form>
            </div>
        </div>
    )
}

export default CRUD;